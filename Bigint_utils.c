/* Datatype for Bigint */
typedef struct Bigint {
	int size;
	int sign;
	char *value;
} Bigint;


/* Fuction to generate substring of given string */
char* Bigint_substr(char *string, int start, int end) {
	// Allocate
	char *substring = (char*)malloc( (end-start+1)*sizeof(char) );
	int s = sizeof(substring);

	// Assign
	int i=0;
	while (start <= end) { *(substring + i) = string[start]; i++; start++; }
	*(substring+i) = '\0';

	s = sizeof(substring);
	
	return substring;
}


/* Function to strip spaces and preceeding zero from string */
char* Bigint_strip(char *number) {

	// Trim the spaces
	int l=0, r=strlen(number)-1;
	while(number[l]==' ' || number[r]==' ') {
		if ( number[l]==' ' ) l++;
		if ( number[r]==' ' ) r--;
	}
	if (l || r!=strlen(number)-1) { number=Bigint_substr(number, l, r); }

	// Length After triming spaces
	int length = strlen(number);

	// Remove Unsignificent 0's
	if ( !isdigit(number[0]) ) {	// If 1st char is sign
		// Get count of Unsignificent 0's
		int count = 0;
		while ( number[count+1] == '0' ) { count++; }
		// Shift left by count position
		if ( count ) {
			// Reduce count by if it only contain 0's
			count = count==length-1 ? count-1 : count;
			char *temp = (char*)malloc(sizeof(char)*(length-count));
			*(temp) = *(number);
			int i = 1;
			while ( i+count <= length ) {
				*(temp + i) = *(number + i+count);
				i++;
			}
			return temp;
		}
	} else {	// If 1st char is not sign
		int count = 0;
		while ( number[count] == '0' ) { count++; }
		if ( count ) {
			// Reduce count by if it only contain 0's
			count = count==length ? count-1 : count;
			number=Bigint_substr(number, count, strlen(number)-1);
		}
	}

	return number;
}


/* Function to extract size & sign and allocate it to string */
char* Bigint_assign( char *s, int size ) {
	// Allocate and copy data
	char *str = (char *)malloc( size*sizeof(char) );
	strcpy(str, s);

	// Strip spaces are remove zero
	str = Bigint_strip(str);

	// If 1st digit is sign
	if ( str[0]=='+' || str[0]=='-' ) { str++; }

	return str;
}


/* Function to check if input string is valid to create Bigint no. */
int Bigint_isStringValid(char *number) {
	// Check for spaces at left and at right
	int l=0, r=strlen(number)-1;
	while(number[l]==' ' || number[r]==' ') {
		if ( number[l]==' ' ) l++;
		if ( number[r]==' ' ) r--;
	}
	// Check for sign
	if (number[l]=='-' || number[l]=='+') {l++;}
	// Check for non-significant 0's
	while ( number[l] == '0' ) { l++; }
	// Check if remaining no. is digit
	for ( int i=l; i<=r; i++ ) {
		if ( !isdigit(number[i]) ) { return 0; }
	}
	return 1;
}


/* Function to set Invalid Bigint no. */
Bigint Bigint_none(char *msg) {
	Bigint temp;

	temp.value = Bigint_assign(msg, strlen(msg));
	temp.size = -1;
	temp.sign = -1;

	return temp;
}


/* Function to check if given Bigint is valid */
int Bigint_isValid( Bigint number ) {

	if (number.size != strlen(number.value))   { return 0; }
	if (number.sign == -1)                     { return 0; }
	if ( !Bigint_isStringValid(number.value) ) { return 0; }

	return 1;

}


/* Function to set Bigint no. */
Bigint Bigint_set( char *number, int valid ) {

	// Strip
	number = Bigint_strip( number );

	// check if input string in valid
	if ( !valid ) {
		if (!strcmp(number,"")) { return Bigint_none("Empty_no"); }
		if (!Bigint_isStringValid(number)) {return Bigint_none("Invalid_no");}
	}

	// If valid then assign
	Bigint temp;
	temp.value = Bigint_assign(number, strlen(number));
	temp.size = strlen(temp.value);
	temp.sign = (isdigit(number[0]) || number[0]=='+') ? 0 : 1;

	return temp;

}


/* Function to Compare only number not sign */
int Bigint_strcmp( Bigint n1, Bigint n2 ) {
	return n1.size==n2.size ? strcmp(n1.value,n2.value) : n1.size-n2.size;
}


/* Function to Compare to Bigint no. */
int Bigint_compare( Bigint num1, Bigint num2 ) {

	// Check if invalid
	if ( !Bigint_isValid(num1) || !Bigint_isValid(num2) ) { return -2; }

	// If sign is opposite
	if ( num1.sign > num2.sign ) { return -1; }
	if ( num1.sign < num2.sign ) { return 1; }

	// Get difference
	long long diff = Bigint_strcmp(num1, num2);

	// if numbers are same
	if ( diff == 0 ) { return diff; }

	// Reduce diff to +1 or -1
	diff /= diff<0 ? -(diff) : diff;
	// If both are negative no.
	if ( num1.sign == 1 ) { return -(diff); }
	// If both are positive no.
	if ( num1.sign == 0 ) { return diff; }

}