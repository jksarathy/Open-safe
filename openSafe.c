
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "safe.h"
#include "openSafe.h"



/* Include safe.h before this file to get the definition of Safe. */

/*
 * Open a safe and return the value returned by tryCombination,
 * or SAFE_SELF_DESTRUCTED if the safe self-destructed.
 */
int* getNextPerm(int tumblers, int positions, int *combo) {
	//go through array backwards (first i = tumblers -1)
	//hold others constant and just increment combo[i] each time
	//if combo[i] = positions, reset to zero and decrement i
	int changed = 0;
	int index = tumblers - 1;

	while (changed == 0 && index >= 0) {
		if (combo[index] < positions - 1) {
			combo[index] += 1;
			changed = 1;
		}
		else {
			combo[index] = 0;
			index = index - 1;
		}
	}
	return combo;
}

void deleteArray(int *array, int length) {
	free(array);
}

int openSafe(Safe *s) {

	int tumblers = numTumblers(s);
	int positions = numPositions(s);
	int i;
	int j;
	int value = -2;
	int true = 1;

	int *combo = malloc(sizeof(int*)*tumblers);
	assert(combo);

	for (i = 0; i < tumblers; i++) {
		combo[i] = 0;
	}

	int *comboCopy = malloc(sizeof(int*)*tumblers);
	assert(comboCopy);

	while (true) {
		combo = getNextPerm(tumblers, positions, combo);
		if (combo == comboCopy) break;

		for (j = 0; j < tumblers; j++) {
			comboCopy[j] = combo[j];
		}

		value = tryCombination(s, comboCopy);
		if (value != SAFE_BAD_COMBINATION) break;
	}

	deleteArray(combo, tumblers);
	deleteArray(comboCopy, tumblers);

	return value;
}


