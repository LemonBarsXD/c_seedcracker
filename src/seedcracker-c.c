/*
 ============================================================================
 Name        : seedcracker-c.c
 Author      : Upwn, LemonBarsXD
 Version     : 1.0
 Copyright   : No
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

	/* Amount of inputs */
	int a;
	fputs("Amount: ", stdout);
	scanf("%d", &a);

	/* Flushing stdout, don't know if it's necessary */
	fflush(stdout);

	/* Initial memory allocation */
	int *uInput = malloc(sizeof(int) * a);

	/* User input */
	for(int i = 0; i < a; i++) {
		printf("%d: ", i+1);
		scanf("%d", &uInput[i]);
	}

	seedcrack(uInput, a); // crack

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

	for(seed = 1; seed < SEARCH_DEPTH; seed++) {
		srand(seed);
		for(int i = 0; i < a; i++) {
				buffer[i] = rand();
			}

		for(int i = 0; i < a; i++) {
			if(input[i] == buffer[i]) {
				if(i+1 == a) {
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
