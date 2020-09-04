#include "./Bigint_utils.c"

char *result;


/* Function to perform addition on no. with same sign */
char *Bigint_addSame(Bigint larger, Bigint smaller) {

	// Shift Variable to get difference in length
	int shift = larger.size - smaller.size;

	// Length varaible with length=max_length+carry+sign
	int length = larger.size + 2;

	// Sum string 
	result = (char *)realloc( result, (length)*sizeof(char) );

	// Carray variable, iteration variable(i)
	int carry = 0;
	int i = length;

	// Set no. in reverse order
	*(result + i--) = '\0';
	while ( i > 0 ) {
		int sum = 0;	// Sum variable
		// Add larger number value
		if ( length-i<=larger.size && i>1 ) { sum += larger.value[i-2] - '0'; }
		// Add smaller number value by shifting i by shift value
		if ( length-i<=smaller.size && i>1 ) { sum += smaller.value[i-shift-2] - '0'; }
		// If carry exist
		if ( carry ) { sum += carry; }

		// Set carry & digit
		*(result + i) = sum%10+'0';
		carry = sum/10;
		i--;
	}
	// set digit sign
	*result = larger.sign ? '-' : '+';

	return result;
	
}


/* Function to perform subtraction on no. with different sign */
char *Bigint_subDiff(Bigint larger, Bigint smaller) {

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

		// Set digit, if second digits, then no need to add '0'
		*(temp + i) = diff + (diff>9 ? 0 : '0');
		i--;
	}
	// set digit sign
	*temp = larger.sign ? '-' : '+';

	return temp;

}


/* Function to perform multiplication all numbers.. */
char *Bigint_mulAll(Bigint num1, Bigint num2) {

	// Temoporary variable, to store array of all product
	char *temp = (char*)malloc( (num2.size*(2*num1.size+num2.size+3)/2)*sizeof(char) );
	// 2nd variable, to store add no. of all stage product and get prouct in reverse format
	char *carry = (char*)malloc( (num1.size+num2.size)*sizeof(char) );
	// Final product variable
	result = (char*)realloc( result, (num1.size+num2.size+1)*sizeof(char) );

	int len1 = num1.size;	// Length variable
	int len2 = num2.size;	// Length variable
	int i, j, k=0;		// First stage Iteration variable
	int x=0, y;		// second stage Iteration variable
	long reminder = 0;	// Get reminder to append at last of string
	long sum = 0;		// Sum variable, to get value of carry at ith place

	// Get Array of product
	for (i=len2-1; i>=0; i--) {
		reminder = 0;	// Reset reminder
		// multiply a digit of B to all digit of A
		for (j=len1-1; j>=0; j--) {
			temp[k++] = ( (num2.value[i]-'0')*(num1.value[j]-'0')+reminder )%10;
			reminder  = ( (num2.value[i]-'0')*(num1.value[j]-'0')+reminder )/10;
		}
		temp[k++] = reminder;	// Append reminder

		// Append 0's to shift
		for (++x,y=0; y<x; y++) { temp[k++] = 0; }
	}

	reminder = 0;	// Reset reminder
	k = 0;	// Reset pointer
	// Get product in reverse order
	for (i=0; i<len1+len2; i++) {
		sum = 0;	// Get sum at ith place
		y = 0;	// Index of temp w.r.t. i in carry
		// Get sum
		for (j=1; j<=len2; j++) {
			if ( i < len1+j) { sum += temp[y+i]; }
			y += j+len1;
		}
		// Set carry & reminder
		carry[k++] = ( sum+reminder )%10;
		reminder = ( sum+reminder )/10;
	}
	// Append reminder
	carry[k] = reminder;

	// Get final product
	j = 0;	// Set pointer
	result[j++] = num1.sign^num2.sign ? '-' : '+';	// Set sign
	// Reverse carry & set result
	for (i=k; i>=0; i--) { result[j++] = carry[i]+'0'; }
	result[j] = '\0';

	// Free allocated memory..
	free(temp);
	free(carry);

	return result;

}


/* Function to perform addition on no. */
Bigint Bigint_add(Bigint n1, Bigint n2) {

	// If not valid
	if (!Bigint_isValid(n1) || !Bigint_isValid(n2)) { return Bigint_none("Invalid_no_to_add"); }

	char *add;	// String to hold add output

	// If no.1 is greater, numerically
	if ( Bigint_strcmp(n1,n2)>=0 ) {
		// If Sign are different, then subtract
		if (n1.sign != n2.sign) { add = Bigint_subDiff(n1, n2); }
		// If sign are same, Then call add function with 1st parameter as larger no.
		else { add = Bigint_addSame(n1, n2); }
	}
	// Else no.2 is greater, numerically
	else {
		// If Sign are different, then subtract
		if (n1.sign != n2.sign) { add = Bigint_subDiff(n2, n1); }
		// If sign are same, Then call add function with 1st parameter as larger no.
		else { add = Bigint_addSame(n2, n1); }
	}

	return Bigint_set(add, 1);

}


/* Function to perform subtraction on no. */
Bigint Bigint_subtract(Bigint n1, Bigint n2) {

	// If not valid
	if (!Bigint_isValid(n1) || !Bigint_isValid(n2)) { return Bigint_none("Invalid_no_to_subtract"); }

	char *sub;	// String to hold subtract output

	// If no.1 is greater, numerically
	if ( Bigint_strcmp(n1,n2)>=0 ) {
		// If Sign are different, then add
		if (n1.sign != n2.sign) { sub = Bigint_addSame(n1, n2); }
		// If sign are same, Then call subtract function with 1st parameter as larger no.
		else { sub = Bigint_subDiff(n1, n2); }
	}
	// Else no.2 is greater, numerically
	else {
		// If Sign are different, then add
		if (n1.sign != n2.sign) { sub = Bigint_addSame(n2, n1); }
		// If sign are same, Then call subtract function with 1st parameter as larger no.
		else { sub = Bigint_subDiff(n2, n1); }
	}

	return Bigint_set(sub, 1);

}


/* Function to perform multiplication on no. */
Bigint Bigint_multiply(Bigint n1, Bigint n2) {

	// If not valid
	if (!Bigint_isValid(n1) || !Bigint_isValid(n2)) { return Bigint_none("Invalid_no_to_multiply"); }

	// String to hold multiply output
	char *mul = Bigint_mulAll(n1, n2);

	return Bigint_set(mul, 1);

}