// writes a descending list of integers to the standard output stream

#include <stdio.h>

void count_down( void ) {
	// (a) Print the introductory message.
	printf("Listing integers in reverse, from 320 down to but not including 100 in steps of 6.\n");

	// (b) Declare an integer variable that you will use to count. Initially 
	//     the counter should equal the start value, 320.
	int counter =320;

	// (c) Begin a WHILE statement that will execute its loop body if the 
	//     counter is greater than the end value, 100.
	while(counter>100)
	{
		printf("%d\n",counter );
		counter=counter-6;
	}

		// (e) Print the value of the counter on a line by itself.

		// (f) Subtract the step size, 6, from the counter.
	// (d) End the WHILE statement
}

int main( void ) {
	count_down();
	return 0;
}