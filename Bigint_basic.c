/* Basic structure of Big Integer */
typedef struct Bigint {

	int size;
	int sign;
	char *value;

} Bigint;


/* Allocate size and value to value of Bigint */
char* Bigint_assign( char *s, int size ) {

	char *str;

	// If 1st digit is sign
	if ( s[0]=='+' || s[0]=='-' ) { size--; s++; }

	// Allocate and copy data
	str = (char *)malloc( size*sizeof(char) );
	strcpy(str, s);

	return str;

}


/* Function to remove preceading 0 and strip spaces */
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


/* Check if given no. string is valid */
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


/* Null pointer for Bigint numbers */
Bigint Bigint_none(char *msg) {

	Bigint temp;

	temp.value = Bigint_assign(msg, strlen(msg));
	temp.size = -1;
	temp.sign = -1;

	return temp;

}

/* Check if given Bigint no. is invalid */
int Bigint_isValid( Bigint number ) {

	if (number.size != strlen(number.value))   { return 0; }
	if (number.sign == -1)                     { return 0; }
	if ( !Bigint_isStringValid(number.value) ) { return 0; }

	return 1;

}


/* Get number */
Bigint Bigint_set( char *number ) {

	// Strip spaces are remove zero
	number = Bigint_strip(number);

	// check if input string in valid
	if (!Bigint_isStringValid(number)) {
		return Bigint_none("ERROR");
	}

	// If valid then assign
	Bigint temp;
	temp.value = Bigint_assign(number, strlen(number));
	temp.size = strlen(temp.value);
	temp.sign = (isdigit(number[0]) || number[0]=='+') ? 0 : 1;
	
	return temp;

}


/* Compare Bigint no. */
int Bigint_compare( Bigint num1, Bigint num2 ) {
	
	// Check if num1 & num2, is valid
	if ( Bigint_isValid(num1) && Bigint_isValid(num2) ) {

		int cmp = strcmp( num1.value, num2.value );

		printf("%s %s %d\n", num1.value, num2.value, cmp);
		
		// Condition to reverse the sign
		if ((cmp==1 && num1.sign) || (cmp==-1 && num2.sign)) { cmp*=-1; }

		printf("%d\n", cmp);

		// Convert to +1, 0, -1 foramt
		if ( cmp ) { cmp /= (cmp<0) ? -(cmp) : cmp; }

		printf("%d\n", cmp);

		return cmp;

	}

	return -2;

}