#ifndef MAT_MUL
#define MAT_MUL

#include <stdlib.h>
#include <stdio.h>

typedef struct matrix {
    size_t width;
    size_t height;
    float  **mat;
} matrix;

//TODO: Description
matrix* mat_init(float *array, size_t array_length, size_t height, size_t width); 

//TODO: Description
int dot(matrix *mat1, matrix *mat2, matrix **ptr);

//TODO: Description
int mat_print(matrix *matrix);

//TODO: Description
int free_mat(matrix *matrix);

#endif
