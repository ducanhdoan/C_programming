// computes the product of the finite elements of a numeric array

#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

double array_product( double arr[],int n ) {
	// TODO: INSERT CODE HERE
	int times=0;
	double multiply=1.0;
	if (n == 0)
	{
		/* code */
		multiply *= NAN;
	}
	else{
		for (int i = 0; i < n; i++)
		{
			/* code */
			if (isfinite(arr[i])==0)
			{
				/* code */
				times+=1;
				if (times==n)
				{
					/* code */
					multiply *= NAN;
				}

			}
			else{
				multiply *= arr[i];
			}
		}
	}

	return multiply;
}

void call_function( const char * label, double x[], int count ) {
	double prod = array_product( x, count );
	printf( "%s\n", label );
	printf( "\tInput data:\n" );

	for ( int i = 0; i < count; i++ ) {
		printf( "\t%d\t%f\n", i, x[i] );
	}

	printf( "\tProduct = %f\n\n", prod );
}

int main( void ) {
	double x1[] = {0};
	call_function( "Count == 0", x1, 0 );
	
	double x2[] = { NAN, +INFINITY, -INFINITY };
	call_function( "No finite values", x2, 3 );

	double x3[] = { 1, 2, 3, 4, 5, 6, 7 };
	call_function( "Several finite values", x3, 7 );

	double x4[] = { 2, M_PI, NAN, 3, INFINITY, 4 };
	call_function( "A mix of finite values and infinities", x4, 6 );
	
	return 0;
}