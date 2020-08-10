/**
 * @brief Datatype for Bigint
 * @param size Store size of Bigint
 * @param sign Store sign of Bigint
 * @param value Store actual no. of Bigint
 */
typedef struct Bigint {

	int size;
	int sign;
	char *value;

} Bigint;

/**
 * @brief Function to extract size & sign and allocate it to string
 * @param s input string no.
 * @param size length of input no.
 * @return Allocated string only containg no.
 */
char* Bigint_assign( char *s, int size ) {

	char *str;

	// If 1st digit is sign
	if ( s[0]=='+' || s[0]=='-' ) { size--; s++; }

	// Allocate and copy data
	str = (char *)malloc( size*sizeof(char) );
	strcpy(str, s);

	return str;

}

/**
 * @brief Function to strip spaces and preceeding zero from string
 * @param number input string no.
 * @return String only containg no. after removing unwanted 0's and spaces
 */
char* Bigint_strip(char *number) {

	// Right trim
	while ( *number == ' ' ) { number++; }

	// Remove zero
	while ( strlen(number)>1 && *number=='0' ) { number++; }

	// Left trim
	char temp[ strlen(number) ];
	strcpy( temp, number );
	while ( temp[strlen(temp)-1]==' ' ) { temp[strlen(temp)-1]='\0'; }
	number = temp;

	return number;

}

/**
 * @brief Function to check if input string is valid to create Bigint no.
 * @param number String no. to check
 * @return integer value 1(Valid) and 0(Invalid)
 */
int Bigint_isStringValid(char *number) {

	// Return false in any char is not no.
	for ( int i=0; i<strlen(number); i++ ) {
		if ( !isdigit(number[i]) ) {
			if ( !(i==0 && (number[i]=='-' || number[i]=='+')) ) {
				return 0;
			}
		}
	}
	return 1;

}

/**
 * @brief Function to set Invalid Bigint no.
 * @param msg message to indicate cause of error
 * @return NULL Bigint with error message
 */
Bigint Bigint_none(char *msg) {

	Bigint temp;

	temp.value = Bigint_assign(msg, strlen(msg));
	temp.size = -1;
	temp.sign = -1;

	return temp;

}

/**
 * @brief Function to check if given Bigint is valid
 * @param number Bigint no. to check
 * @return integer value 1(Valid) and 0(Invalid)
 */
int Bigint_isValid( Bigint number ) {

	if (number.size != strlen(number.value))   { return 0; }
	if (number.sign == -1)                     { return 0; }
	if ( !Bigint_isStringValid(number.value) ) { return 0; }

	return 1;

}

/**
 * @brief Function to set Bigint no.
 * @param number No. string to be allogated to Bigint
 * @return Bigint no. of given no. string
 */
Bigint Bigint_set( char *number ) {

	// Strip spaces are remove zero
	number = Bigint_strip(number);

	// check if input string in valid
	if (!Bigint_isStringValid(number)) {
		return Bigint_none("Invalid Number");
	}

	// If valid then assign
	Bigint temp;
	temp.value = Bigint_assign(number, strlen(number));
	temp.size = strlen(temp.value);
	temp.sign = (isdigit(number[0]) || number[0]=='+') ? 0 : 1;

	return temp;

}


/**
 * @brief Function to Compare to Bigint no.
 * @param num1 Bigint no. 1
 * @param num2 Bigint no. 2
 * @return integer value 0(equal), 1(not equal) and -2(invalid)
 */
int Bigint_compare( Bigint num1, Bigint num2 ) {

	return -2;

}