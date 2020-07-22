#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "Bigint_basic.c"

int bigvalid(Bigint number) { Bigint_isNone(number); }
Bigint bignull() { Bigint_none(); }
Bigint bigset(char *string) { Bigint_set(string); }
int bigcmp(Bigint n1, Bigint n2) { Bigint_compare(n1, n2); }