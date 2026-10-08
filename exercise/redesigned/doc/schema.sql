CREATE TABLE IF NOT EXISTS orders (
    id INTEGER PRIMARY KEY,
    customer INTEGER NOT NULL,
    subtotal_cents INTEGER NOT NULL CHECK (subtotal_cents >= 0),
    weight_grams INTEGER NOT NULL CHECK (weight_grams >= 0),
    shipping INTEGER NOT NULL CHECK (shipping IN (1,2)),
    status INTEGER NOT NULL CHECK (status IN (0,1))
);
CREATE TABLE IF NOT EXISTS order_items (
    order_id INTEGER NOT NULL REFERENCES orders(id) ON DELETE CASCADE,
    position INTEGER NOT NULL,
    article_code VARCHAR(40) NOT NULL,
    quantity INTEGER NOT NULL CHECK (quantity > 0),
    unit_price_cents INTEGER NOT NULL CHECK (unit_price_cents >= 0),
    PRIMARY KEY (order_id, position)
);
