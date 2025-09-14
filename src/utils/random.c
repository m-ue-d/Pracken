#include "random.h"

/*
returns a random number between 0 and limit (limit exclusive)
*/
int rand_lim(int limit) {

    int div = RAND_MAX / limit;
    int result;

    do {
        result = rand() / div;
    } while (result >= limit);

    return result;
}