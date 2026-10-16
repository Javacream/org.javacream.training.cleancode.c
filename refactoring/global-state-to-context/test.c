/* Gemeinsamer Verhaltenstest fuer before und after (ANSI C90). */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "test_adapter.h"
static int failures=0;
#define CHECK_INT(actual,expected) do { int a=(actual); int e=(expected); if(a!=e){fprintf(stderr,"FAIL line %d: %d != %d\n",__LINE__,a,e);failures++;} } while(0)
#define CHECK_NEAR(actual,expected) do { double a=(actual); double e=(expected); if(fabs(a-e)>0.000001){fprintf(stderr,"FAIL line %d: %.9g != %.9g\n",__LINE__,a,e);failures++;} } while(0)
int main(void){
CHECK_INT(count_after(0),0); CHECK_INT(count_after(2),2); CHECK_INT(count_after(3),5);
if(failures){fprintf(stderr,"%d test(s) failed\n",failures);return 1;} puts("PASS: global-state-to-context");return 0;
}
