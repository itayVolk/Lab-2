/* Represents an unsorted set and contains methods related to it
   Author: Itay Volk
   Date: 10/2/2024
*/

#include "set.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static int search(SET *sp, char *elt);

typedef struct set {
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

/* Adds a copy of the element to the end of the set (no duplicates)
   O(n)
*/
void addElement(SET *sp, char *elt) {
    assert(sp != NULL);
    assert(elt != NULL);
    if (search(sp, elt) == -1){
        sp->data[sp->n++] = strdup(elt);
    }
}

/* Removes the element and shifts every item after of it backwards
   O(n)
*/
void removeElement(SET *sp, char *elt) {
    assert(sp != NULL);
    assert(elt != NULL);
    int i = search(sp, elt);
    if (i != -1) {
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
   O(n)
*/
char *findElement(SET *sp, char *elt) {
    assert(sp != NULL);
    assert(elt != NULL);
    int i = search(sp, elt);
    return i == -1 ? NULL : sp->data[i];
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

/* Linear search over the set (returns -1 if not found)
   Best: O(1)
   Average: O(n)
   Worst: O(n)
*/
static int search(SET *sp, char *elt) {
    for (int i = 0; i < sp->n; i++) {
        if (!strcmp(sp->data[i], elt)) {
            return i;
        }
    }
    return -1;
}
