/* Represents a sorted set and contains methods related to it
   Author: Itay Volk
   Date: 10/3/2024
*/

#include "set.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>

static int search(SET *sp, char *elt, bool *found);

typedef struct set {
    int n;
    int count;
    char **data;
} SET;

/* Creates a new set that can contain up to maxElts many items
   O(1)
*/
SET *createSet(int maxElts) {
    SET* set = malloc(sizeof(SET));
    assert (set != NULL);
    set->count = maxElts;
    set->n = 0;
    set->data = calloc(maxElts, sizeof(char*));
    assert (set->data != NULL);
    return set;
}

/* Destroys the set and frees all related memory
   O(n)
*/
void destroySet(SET *sp) {
    assert(sp != NULL);
    for (int i = 0; i < sp->n; i++) {
        free(sp->data[i]);
    }
    free(sp->data);
    free(sp);
}

/* Returns the number of elements in the set
   O(1)
*/
int numElements(SET *sp) {
    assert(sp != NULL);
    return sp->n;
}

/* Adds a copy of the element to the appropriate spot in the set (no duplicates)
   O(n)
*/
void addElement(SET *sp, char *elt) {
    assert(sp != NULL);
    assert(elt != NULL);
    bool found = false;
    int i =  search(sp, elt, &found) + 1;
    if (!found) {
        sp->n++;
        assert(sp->n <= sp->count);
        for (int j = sp->n; j > i; j--) {
            sp->data[j] = sp->data[j-1];
        }
        sp->data[i] = strdup(elt);
        assert(sp->data[i] != NULL);
    }
}

/* Removes the element and shifts every item after of it backwards
   O(log(n))
*/
void removeElement(SET *sp, char *elt) {
    assert(sp != NULL);
    assert(elt != NULL);
    bool found = false;
    int i = search(sp, elt, &found);
    if (found) {
        free(sp->data[i]);
        i++;
        for (; i < sp->n; i++) {
            sp->data[i-1] = sp->data[i];
        }
        sp->n--;
    }
}

/* Returns a pointer to the spot in the set which contains the value of elt
   O(log(n))
*/
char *findElement(SET *sp, char *elt) {
    assert(sp != NULL);
    assert(elt != NULL);
    bool found = false;
    int i = search(sp, elt, &found);
    return found ? sp->data[i] : NULL;
}

/* Returns an array containing a copy of the data in the set
   O(n)
*/
char **getElements(SET *sp) {
    assert(sp != NULL);
    char **out = calloc(sp->n, sizeof(char*));
    assert(out != NULL);
    for (int i = 0; i < sp->n; i++) {
        out[i] = strdup(sp->data[i]);
        assert(out[i] != NULL);
    }
    return out;
}

/* Binary search over the set (stores whether it's in the set in found)
   Best: O(1)
   Average: O(log n)
   Worst: O(log n)
*/
static int search(SET *sp, char *elt, bool *found) {
    assert(sp != NULL);
    assert(elt != NULL);
    if (sp->n == 0) {
        *found = false;
        return -1;
    }
    int lo = 0, mid, hi = sp->n-1;
    while (lo <= hi) {
	mid = (lo+hi)/2;
	int comp = strcmp(sp->data[mid], elt);
        if (comp == 0) {
		*found = true;
		return mid;
	} else if (comp < 0) {
		lo = mid + 1;
	} else {
		hi = --mid;
	}
    }
    *found = false;
    return  mid;
}
