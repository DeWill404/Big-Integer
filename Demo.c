#include <stdio.h>

#include "BigInt.c"



void main () {

	Bigint n1 = bigset("100");

	printf("%s %d %d\n", n1.value, n1.size, n1.sign);

}