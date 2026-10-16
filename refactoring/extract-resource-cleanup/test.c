/* Gemeinsamer Verhaltenstest fuer before und after (ANSI C90). */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "test_adapter.h"
static int failures=0;
#define CHECK_INT(actual,expected) do { int a=(actual); int e=(expected); if(a!=e){fprintf(stderr,"FAIL line %d: %d != %d\n",__LINE__,a,e);failures++;} } while(0)
#define CHECK_NEAR(actual,expected) do { double a=(actual); double e=(expected); if(fabs(a-e)>0.000001){fprintf(stderr,"FAIL line %d: %.9g != %.9g\n",__LINE__,a,e);failures++;} } while(0)
static int check_file(const char *path,const char *expected){FILE *f=fopen(path,"r");char buf[64];int ok;if(!f)return 0;ok=fgets(buf,sizeof buf,f)!=NULL && strcmp(buf,expected)==0;fclose(f);return ok;}
int main(void){
CHECK_INT(write_case("test-output.txt",42),0); CHECK_INT(check_file("test-output.txt","42\n"),1); CHECK_INT(write_case("test-output.txt",-8),0); CHECK_INT(check_file("test-output.txt","-8\n"),1); CHECK_INT(write_case("/this-path-should-not-exist/clean-code.txt",42),-1); remove("test-output.txt");
if(failures){fprintf(stderr,"%d test(s) failed\n",failures);return 1;} puts("PASS: extract-resource-cleanup");return 0;
}
