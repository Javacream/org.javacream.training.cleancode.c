#include <stdio.h>
#include "../src/application.h"

static unsigned failures = 0U;
#define CHECK(expr) do { if (!(expr)) { \
    fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #expr); \
    ++failures; \
} } while (0)

/* Dummy: Ein Platzhalterobjekt, dessen Inhalt niemals gelesen wird. */
typedef struct {
    int unused;
} DummyStorageContext;

/* Stub: Liefert ein festes Ergebnis, ohne Eingaben auszuwerten. */
static int successful_stub(void *user_data, int order_id, int amount)
{
    (void)user_data;
    (void)order_id;
    (void)amount;
    return 1;
}

/* Mock: zeichnet Aufrufe auf und erlaubt die Pruefung der Interaktion. */
typedef struct {
    unsigned calls;
    int last_order_id;
    int last_amount;
    int result;
} MockStorage;

static int mock_save(void *user_data, int order_id, int amount)
{
    MockStorage *mock = (MockStorage *)user_data;
    ++mock->calls;
    mock->last_order_id = order_id;
    mock->last_amount = amount;
    return mock->result;
}

static void test_with_dummy_and_stub(void)
{
    ApplicationContext app;
    StorageDependency dep;
    DummyStorageContext dummy = {0};
    dep.save = successful_stub;
    dep.user_data = &dummy;

    CHECK(application_init(&app, dep) == 1);
    CHECK(process_order(&app, 10, 50) == 1);
    CHECK(app.requests == 1U);
    /* Dummy wird nicht ausgewertet; der Stub liefert immer Erfolg. */
}

static void test_mock_verifies_interaction(void)
{
    ApplicationContext app;
    StorageDependency dep;
    MockStorage mock = {0U, 0, 0, 1};
    dep.save = mock_save;
    dep.user_data = &mock;

    CHECK(application_init(&app, dep) == 1);
    CHECK(process_order(&app, 17, 250) == 1);
    CHECK(mock.calls == 1U);
    CHECK(mock.last_order_id == 17);
    CHECK(mock.last_amount == 250);
    CHECK(app.requests == 1U);
}

static void test_mock_failure_and_invalid_input(void)
{
    ApplicationContext app;
    StorageDependency dep;
    MockStorage mock = {0U, 0, 0, 0};
    dep.save = mock_save;
    dep.user_data = &mock;

    CHECK(application_init(&app, dep) == 1);
    CHECK(process_order(&app, 21, 90) == 0);
    CHECK(mock.calls == 1U);
    CHECK(app.requests == 1U);
    CHECK(process_order(&app, -1, 90) == 0);
    CHECK(process_order(&app, 22, -1) == 0);
    CHECK(mock.calls == 1U);
    CHECK(app.requests == 1U);
}

static void test_separate_contexts_and_invalid_dependency(void)
{
    ApplicationContext a;
    ApplicationContext b;
    StorageDependency dep;
    dep.save = successful_stub;
    dep.user_data = 0;
    CHECK(application_init(&a, dep) == 1);
    CHECK(application_init(&b, dep) == 1);
    CHECK(process_order(&a, 1, 0) == 1);
    CHECK(a.requests == 1U);
    CHECK(b.requests == 0U);
    CHECK(process_order(0, 1, 0) == 0);
    dep.save = 0;
    CHECK(application_init(&b, dep) == 0);
}

int main(void)
{
    test_with_dummy_and_stub();
    test_mock_verifies_interaction();
    test_mock_failure_and_invalid_input();
    test_separate_contexts_and_invalid_dependency();
    if (failures != 0U) {
        fprintf(stderr, "%u assertion(s) failed\n", failures);
        return 1;
    }
    puts("All CDI tests passed");
    return 0;
}
