#include "matmul.h"

//TODO: Guardrailing
matrix* mat_init(float *array, size_t array_length, size_t height, size_t width) {
    matrix *new_matrix = malloc(sizeof(matrix));
    new_matrix->height = height;
    new_matrix->width  = width;

    new_matrix->mat = malloc(height * sizeof(float*));

    if (array == NULL) {
        for (size_t i = 0; i < height; i++) {
            new_matrix->mat[i] = calloc(width, sizeof(float));
        }
        return new_matrix;
    }

    for (size_t i = 0; i < height; i++) {
        new_matrix->mat[i] = malloc(width * sizeof(float));
    }

    size_t i = 0;
    while (i < array_length) {
        for (size_t m = 0; m < height; m++) {
            for (size_t n = 0; n < width; n++) {
                new_matrix->mat[m][n] = array[i];
                i++;
            }
        }
    }
    return new_matrix;
}

//TODO: Guardrailing
int dot(matrix *mat1, matrix *mat2, matrix **ptr) {
    size_t result_h = mat1->height;
    size_t result_w = mat2->width;
    size_t shared_index = mat1->width;

    matrix *result = malloc(sizeof(matrix));
    result->height = result_h;
    result->width  = result_w;
    
    result->mat = malloc(result_h * sizeof(float*));
    for (size_t i = 0; i < result_h; i++) {
        result->mat[i] = calloc(result_w, sizeof(float));
    }
    
    for (size_t row = 0; row < result_h; row++) {
        for (size_t col = 0; col < result_w; col++) {
            for (size_t i = 0; i < shared_index; i++) {
                result->mat[row][col] += mat1->mat[row][i] * mat2->mat[i][col];
            }
        }
    }

    *ptr = result;
    return 0;
}

//TODO: Guardrailing
int mat_print(matrix *matrix) {
    int height = matrix->height;
    int width  = matrix->width;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            printf("%.2f ", matrix->mat[row][col]);
        }
        printf("\n");
    }
    return 0;
}

//TODO: Guardrailing
int free_mat(matrix *matrix) {
    free(matrix->mat);
    free(matrix);
    return 0;
}
