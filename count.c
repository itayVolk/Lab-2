/* Represents a sorted set and contains methods related to it
   Author: Itay Volk
   Date: 10/1/2024
*/

#include "set.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

static int search(SET *sp, char *elt, bool *found);

typedef struct set {
	int length;    
	int n;
    char **data;
} SET;

/* Creates a new set that can contain up to maxElts many items
   O(1)
*/
SET *createSet(int maxElts) {
    SET* set = malloc(sizeof(SET));
    assert (set != NULL);
    set->n = 0;
    set>length = 0;
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
    bool found;
    int i = search(sp, elt, &found);
    if (found) {
        if (i == sp->n) {
            sp->n++;
        }
	assert(sp->n != sp->count);
        for (int j = sp->n; j > i; j--) {
            sp->data[j] = sp->data[j-1];
        }
        sp->data[i] = strdup(elt);
    }
}

/* Removes the element and shifts every item after of it backwards
   O(log(n))
*/
void removeElement(SET *sp, char *elt) {
    assert(sp != NULL);
    assert(elt != NULL);
    bool found;
    int i = search(sp, elt, &found);
    if (found) {
        free(sp->data[i]);
        if (i < sp->n) {
            i++;
            for (; i < sp->n; i++) {
                sp->data[i-1] = sp->data[i];
            }
            sp->n--;
        }
    }
}

/* Returns a pointer to the spot in the set which contains the value of elt
   O(log(n))
*/
char *findElement(SET *sp, char *elt) {
    assert(sp != NULL);
    assert(elt != NULL);
    bool found;
    int i = search(sp, elt, &found);
    return found ? sp->data[i] : NULL;
}

/* Returns an array containing a copy of the data in the set
   O(n)
*/
char **getElements(SET *sp) {
    assert(sp != NULL);
    char **out = calloc(sp->n, sizeof(char*));
    for (int i = 0; i < sp->n; i++) {
        out[i] = strdup(sp->data[i]);
    }
    return out;
}

static int ceiling (double x) {
	return (int)x == x ? (int)x : (int)x+1;
}

/* Binary search over the set (stores whether it's in the set in found)
   Best: O(1)
   Average: O(log n)
   Worst: O(log n)
*/
static int search(SET *sp, char *elt, bool *found) {
    int n = sp->n;
    int i = ceiling(n/2.0);
    while (strcmp(sp->data[i], elt) && n > 1) {
        n = ceiling(n/2.0);
        if (strcmp(sp->data[i], elt) > 0) {
            i -= n;
        } else {
            i += n;
        }
    }
    *found = !strcmp(sp->data[i], elt);
    return  i;
}
