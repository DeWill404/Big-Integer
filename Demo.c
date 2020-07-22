#include <stdio.h>

#include "BigInt.c"



void main () {

	char *a = "12345678901234567";
	char *b = "-22345678901234567";
	char *c = "+32345678901234567";
	char *e = "-3234d678G01234567";

	// Set value
	Bigint A = bigset(a);
	Bigint B = bigset(b);
	Bigint C = bigset(c);
	Bigint E = bigset(e);

	// Print data
	printf("A -> %20s %5d %5d\n", A.value, A.size, A.sign);
	printf("B -> %20s %5d %5d\n", B.value, B.size, B.sign);
	printf("C -> %20s %5d %5d\n", C.value, C.size, C.sign);
	printf("E -> %20s %5d %5d\n", E.value, E.size, E.sign);

	// Compare no.
	printf("A - B  ->  %d\n", bigcmp(A,B));
	printf("A - C  ->  %d\n", bigcmp(A,C));
	printf("B - A  ->  %d\n", bigcmp(B,A));
	printf("B - C  ->  %d\n", bigcmp(B,C));
	printf("C - A  ->  %d\n", bigcmp(C,A));
	printf("C - B  ->  %d\n", bigcmp(C,B));
	printf("A - E  ->  %d\n", bigcmp(A,E));
	printf("B - E  ->  %d\n", bigcmp(B,E));
	printf("C - E  ->  %d\n", bigcmp(C,E));

	// Check if null or set null
	printf("IS E valid %d\n", bigvalid(E));
	printf("IS A valid %d\n", bigvalid(A));
	A = bignull();
	printf("IS A valid %d\n", bigvalid(A));

}