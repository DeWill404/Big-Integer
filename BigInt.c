#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "Bigint_basic.c"
#include "Bigint_arithmatic.c"

int bigvalid(Bigint number) { 
	return Bigint_isValid(number); 
}

Bigint bignull(char msg[]) { 
	return Bigint_none(msg); 
}

Bigint bigset(char *string) {
	return Bigint_set(string); 
}

int bigcmp(Bigint n1, Bigint n2) { 
	return Bigint_compare(n1, n2); 
}

Bigint bigadd(Bigint n1, Bigint n2) {
	return Bigint_add(n1, n2);
}