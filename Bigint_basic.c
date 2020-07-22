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
	if ( !isdigit(s[0]) ) { size--; s++; }

	// Allocate and copy data
	str = (char *)malloc( size*sizeof(char) );
	strcpy(str, s);

	return str;

}


/* Check if given no. string is valid */
int Bigint_isValid(char *number) {

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
Bigint Bigint_none() {

	Bigint temp;

	temp.value = Bigint_assign(" e", 2);
	temp.size = -1;
	temp.sign = -1;

	return temp;

}

/* Check if given Bigint no. is invalid */
int Bigint_isNone( Bigint number ) {

	if (number.size != strlen(number.value)) { return 0; }
	if (number.sign == -1) 					 { return 0; }
	if ( !Bigint_isValid(number.value) ) 	 { return 0; }

	return 1;

}


/* Get number */
Bigint Bigint_set( char *number ) {

	if (!Bigint_isValid(number)) { return Bigint_none(); }

	Bigint temp;
	temp.value = Bigint_assign(number, strlen(number));
	temp.size = strlen(temp.value);
	temp.sign = (isdigit(number[0]) || number[0]=='+') ? 0 : 1;
	
	return temp;

}


/* Compare Bigint no. */
int Bigint_compare( Bigint num1, Bigint num2 ) {
	
	// Check if num1 & num2, is valid
	if ( Bigint_isNone(num1) && Bigint_isNone(num2) ) {

		int cmp = strcmp( num1.value, num2.value );
		
		// Condition to reverse the sign
		if ((cmp==1 && num1.sign) || (cmp==-1 && num2.sign)) { cmp*=-1; }

		// Convert to +1, 0, -1 foramt
		cmp /= (cmp<0) ? -(cmp) : cmp;

		return cmp;

	}

	return -2;

}