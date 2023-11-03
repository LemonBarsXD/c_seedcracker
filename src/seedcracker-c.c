/*
 ============================================================================
 Name        : seedcracker-c.c
 Author      : Upwn, LemonBarsXD
 Version     : 1.0
 Copyright   : MIT License, Copyright (c) 2023 Upwn
 Description : Rand seedcracker in c
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

/* Amount of seeds to search
 	 * Default is 0x7FFFFF
 	 * This larger the value the longer it takes to open the executable (idk why)
*/
#define SEARCH_DEPTH (0x7FFFFF)

/* RAND_MAX is the maximum value that may be returned by rand.
	* The minimum is zero.
	* Default is 0x7FFF or 32767.
	* It is declared in the stdlib.h header file.
	* I don't know how to change it, figure it out yourself lol.
*/

void clearArray( int *array, int size ); // clearing the array by size (zeroing)
void seedcrack( int input[], int a ); // takes input(s) and amount of input(s)


int main(void) {

	/* Initial memory allocation */
	int a;
	int *uInput;

	/* User input */
	fputs("Amount: ", stdout);
	scanf("%d", &a);

	uInput = malloc(sizeof(int) * a);
	for(int i = 0; i < a; i++) {
		printf("%d: ", i+1);
		scanf("%d", &uInput[i]);
	}

	/* Crack */
	seedcrack(uInput, a);

	/* Memory deallocation*/
	free(uInput);

	/* Exiting */
	return EXIT_SUCCESS;
}

void clearArray( int *array, int size ) {
	for(int i = 0; i < size; i++) {
		array[i] = 0;
	}
}


void seedcrack( int input[], int a ) {
	int buffer[a];
	unsigned int seed;


	// TODO: Maybe faster and more optimised

	for(seed = 1; seed < SEARCH_DEPTH; seed++) {
		srand(seed);
		for(unsigned int i = 0; i < a; i++) {
				buffer[i] = rand();
			}

		for(unsigned int j = 0; j < a; j++) {
			if(input[j] == buffer[j]) {
				if(j+1 == a) {
					printf("\rseed: %d\n", seed);
					clearArray(buffer, a);
				}
			}else {
				clearArray(buffer, a);
				break;
			}
		}
		printf("\r%.3f %%", (float) seed/SEARCH_DEPTH*100); // printf the progress in percent with 3 decimal accuracy
	}

}
