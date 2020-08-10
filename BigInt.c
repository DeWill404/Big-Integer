#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "Bigint_utils.c"

/**
 * @brief Function to check if given Bigint is valid
 * @param number Bigint no. to check
 * @return integer value 1(Valid) and 0(Invalid)
 */
int bigvalid(Bigint number) { return Bigint_isValid(number); }

/**
 * @brief Function to set Invalid Bigint no.
 * @param msg message to indicate cause of error
 * @return NULL Bigint with error message
 */
Bigint bignull(char msg[]) { return Bigint_none(msg); }

/**
 * @brief Function to set Bigint no.
 * @param number No. string to be allogated to Bigint
 * @return Bigint no. of given no. string
 */
Bigint bigset(char *string) { return Bigint_set(string); }

/**
 * @brief Function to Compare to Bigint no.
 * @param num1 Bigint no. 1
 * @param num2 Bigint no. 2
 * @return integer value 0(equal), 1(not equal) and -2(invalid)
 */
int bigcmp(Bigint n1, Bigint n2) { return Bigint_compare(n1, n2); }
