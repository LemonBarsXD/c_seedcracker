/*
 ============================================================================
 Name        : seedcracker-c.c
 Author      : Linus.T, LemonBarsXD
 Version     : 2.0
 Description : stdlib Rand() seedcracker in c
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* SEARCH_DEPTH is the amount of seeds to search
 	 * This larger the value the longer it takes to open the executable (idk why)
*/

#define SEARCH_DEPTH 	0x7FFFF
#define MAX_RAND	100

/* RAND_MAX is the maximum value that may be returned by rand.
	* Default is 0x7FFF or 32767.
*/

void clearArray( unsigned int *array, int size 		    );  // clearing the array (zeroing)
void seedcrack ( unsigned int *input, unsigned int count    );  // bruteforce seedcrack


int main(int argc, char **argv) {


	if(argc == 1)
	{
		fprintf(stderr, "Usage: ./seedcracker {arg1} {arg2}...\n");
		return 1;
	}
	
	for(int i = 1; i < argc; ++i)
	{
		int arg = atoi(argv[i]); // expecting no error
		if(arg > MAX_RAND)
		{
			fprintf(stderr, "arg%d: %d, is bigger than MAX_RAND: %d \n", i, arg, MAX_RAND);
			return 1;
		}
	}

	size_t inputSize = sizeof(unsigned int) * (argc - 1);
    	if (inputSize / sizeof(unsigned int) != (size_t)(argc - 1)) {
        	fprintf(stderr, "Too many arguments, allocation size too large.\n");
        	return 1;
    	}

	unsigned int *uInput = malloc(sizeof(unsigned int) * (argc-1));
	if(uInput == NULL)
	{
		fprintf(stderr, "Memory allocation failed.\n");
	}

	for(int i = 1; i < argc; ++i)
	{
		uInput[i-1] = atoi(argv[i]); // expecting no error
	}

	clock_t start = clock(); // Start timing
    	seedcrack(uInput, argc - 1);
    	clock_t end = clock(); // End timing

    	printf("Execution time: %.2f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);


	free(uInput);

	return 0;
}

void clearArray( unsigned int *array, int size ) {
	for(int i = 0; i < size; ++i) {
		array[i] = 0;
	}
}

void seedcrack(unsigned int *input, unsigned int count ) {
	unsigned int seed;
	unsigned int buffer[count];

	for ( seed = 1; seed < SEARCH_DEPTH; ++seed ) 
	{
		srand(seed);
		
		for ( size_t i = 0; i < count; ++i ) 
		{
			buffer[i] = rand() % MAX_RAND;
		}

		if ( memcmp(input, buffer, count * sizeof(unsigned int)) == 0 ) 
		{
			printf("\rFound seed %d\n", seed);
		}
		
		
		if ( seed % 1000 == 0 ) {
			printf("\r%.3f %%", (float) seed / SEARCH_DEPTH * 100); // prints the progress in percent with 3 decimal accuracy to console
		}
	}
	
	printf("\nDONE!\n");
}
