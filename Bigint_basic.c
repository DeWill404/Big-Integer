#include "./Bigint_utils.c"

/* Function to perform addition on no. with same sign */
Bigint Bigint_addSame(Bigint larger, Bigint smaller) {

	// Shift Variable to get difference in length
	int shift = larger.size - smaller.size;

	// Length varaible with length=max_length+carry+sign
	int length = larger.size + 2;

	// Sum string 
	char* temp = (char *)malloc( (length)*sizeof(char) );

	// Carray variable, iteration variable(i)
	int carry = 0;
	int i = length;

	// Set no. in reverse order
	*(temp + i--) = '\0';
	while ( i > 0 ) {
		int sum = 0;	// Sum variable
		// Add larger number value
		if ( length-i<=larger.size && i>1 ) { sum += larger.value[i-2] - '0'; }
		// Add smaller number value by shifting i by shift value
		if ( length-i<=smaller.size && i>1 ) { sum += smaller.value[i-shift-2] - '0'; }
		// If carry exist
		if ( carry ) { sum += carry; }

		// Set carry & digit
		*(temp + i) = sum%10+'0';
		carry = sum/10;
		i--;
	}
	// set digit sign
	*temp = larger.sign ? '-' : '+';

	return Bigint_set( temp, 1);
	
}


/* Function to perform subtraction on no. with same different */
Bigint Bigint_subDiff(Bigint larger, Bigint smaller) {

	// Shift Variable to get difference in length
	int shift = larger.size - smaller.size;

	// Length varaible with length=max_length+sign
	int length = larger.size + 1;

	// Difference string 
	char* temp = (char *)malloc( (length)*sizeof(char) );

	// Borrow variable, iteration variable(i)
	int borrow = 0;
	int i = length;

	// Set no. in reverse order
	*(temp + i--) = '\0';
	while ( i > 0 ) {
		int diff = -(borrow);	// Difference variable, set with borrow
		// Add larger number value
		if ( length-i<=larger.size ) {
			diff += larger.value[i-1];
		}
		// Subtract smaller number value by shifting i by shift value
		if ( length-i<=smaller.size ) {
			// If current digit is less the at borrow(10), and set borrow=1
			if ( diff < smaller.value[i-shift-1] ) { diff += 10; borrow = 1; }
			// Reser borrow = 0
			else { borrow = 0; }
			diff -= smaller.value[i-shift-1];
		}

		// Set digit
		*(temp + i) = diff+'0';
		i--;
	}
	// set digit sign
	*temp = larger.sign ? '-' : '+';

	return Bigint_set( temp, 1);

}


/* Function to perform addition on no. */
Bigint Bigint_add(Bigint n1, Bigint n2) {

	// If not valid
	if (!Bigint_isValid(n1) || !Bigint_isValid(n2)) { return Bigint_none("Invalid_no_to_add"); }

	// If Sign are different, then subtract
	if ( n1.sign!=n2.sign )
		return Bigint_strcmp(n1,n2)>=0 ?Bigint_subDiff(n1, n2) :Bigint_subDiff(n2, n1);

	// If sign are same, Then call add function with 1st parameter as larger no.
	return Bigint_strcmp(n1,n2)>=0 ? Bigint_addSame(n1, n2) : Bigint_addSame(n2, n1);

}


/* Function to perform subtraction on no. */
Bigint Bigint_subtract(Bigint n1, Bigint n2) {

	// If not valid
	if (!Bigint_isValid(n1) || !Bigint_isValid(n2)) { return Bigint_none("Invalid_no_to_subtract"); }

	// If Sign are different, then add function
	if ( n1.sign!=n2.sign )
		return Bigint_strcmp(n1,n2)>=0 ? Bigint_addSame(n1, n2) : Bigint_addSame(n2, n1);

	// If sign are same, Then call subtract function
	return Bigint_strcmp(n1,n2)>=0 ?Bigint_subDiff(n1, n2) : Bigint_subDiff(n2, n1);

}