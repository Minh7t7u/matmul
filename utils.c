#include "utils.h"

//TODO: Guardrailing
int rand_arr(float *ptr, size_t length) {
    srand(time(0));
    for (size_t i = 0; i < length; i++) {
        ptr[i] = (float) rand() / (float) RAND_MAX;
    }
    return 0;
}
