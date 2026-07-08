#include "matmul.h"

mat_status mat_init(float *array, size_t array_length, matrix *mat, size_t height, size_t width) {
    if (array == NULL) { return ERNULL;}
    if (height * array_length * width == 0) { return ERSIZE;}
    if (height * width != array_length) { return ERSIZE;}

    mat->height = height;
    mat->width  = width;
    mat->data   = array;

    return SUCCESS;
}

mat_status mat_create(matrix *mat, size_t height, size_t width) {
    if (mat == NULL) return ERNULL;
    if (height * width == 0) return ERSIZE;
    mat->data = malloc(sizeof(float) * height * width);
    if (mat->data == NULL) return ERNULL;
    mat->height = height;
    mat->width  = width;
    return SUCCESS;
}
static inline float* mat_safe(matrix *mat, size_t row, size_t col) {
    assert(row >= 0 && row < mat->height && "Row index out of bound");
    assert(col >= 0 && col < mat->width &&  "Column index out of bound");
    return &mat->data[row * (mat->width) + col];
}

static inline float* mat_safe_const(const matrix *mat, size_t row, size_t col) {
    assert(row >= 0 && row < mat->height && "Row index out of bound");
    assert(col >= 0 && col < mat->width &&  "Column index out of bound");
    return &mat->data[row * (mat->width) + col];
}

mat_status mat_add(const matrix *restrict mat1, const matrix *restrict mat2, matrix *restrict ptr) {
    if (mat1 == NULL || mat2 == NULL || ptr == NULL) {
        return ERNULL;
    }
    if (mat1->height != mat2->height || mat2->height != ptr->height) {
        return ERSHAPE;
    }
    if (mat1->width != mat2->width || mat2->width != ptr->width) {
        return ERSHAPE;
    }
    for (size_t k = 0; k < (mat1->width * mat1->height); k++) {
        ptr->data[k] = mat1->data[k] + mat2->data[k];
    }
    return SUCCESS;
}

mat_status mat_sub(const matrix *restrict mat1, const matrix *restrict mat2, matrix *restrict ptr) {
    if (mat1 == NULL || mat2 == NULL || ptr == NULL) {
        return ERNULL;
    }
    if (mat1->height != mat2->height || mat2->height != ptr->height) {
        return ERSHAPE;
    }
    if (mat1->width != mat2->width || mat2->width != ptr->width) {
        return ERSHAPE;
    }
    for (size_t k = 0; k < (mat1->width * mat1->height); k++) {
        ptr->data[k] = mat1->data[k] - mat2->data[k];
    }
    return SUCCESS;
}

mat_status mat_dot(const matrix *restrict mat1, const matrix *restrict mat2, matrix *restrict ptr) {
    if (mat1 == NULL || mat2 == NULL || ptr == NULL) {
        return ERNULL;
    }
    if (mat1->width != mat2->height) {
        return ERSHAPE;
    }
    if (mat1->height != ptr->height || mat2->width != ptr->width) {
        return ERSHAPE;
    }
    for (size_t r = 0; r < mat1->height; r++) {
        for (size_t k = 0; k < mat1->width; k++) {
            for (size_t c = 0; c < mat2->width; c++) {
                ptr->data[r * ptr->width + c] += mat1->data[r * mat1->width + k] 
                                               * mat2->data[k * mat2->width + c];
            }
        }
    }
    return SUCCESS;
}

mat_status mat_scale(const matrix *restrict mat, float scalar, matrix *restrict ptr) {
    if (mat == NULL || ptr == NULL) {
        return ERNULL;
    }
    if (mat->height != ptr->height || mat->width != ptr->width) {
        return ERSHAPE;
    }
    for (size_t k = 0; k < (mat->width * mat->height); k++) {
        ptr->data[k] = mat->data[k] * scalar;
    }
    return SUCCESS;
}

mat_status mat_destroy(matrix *mat, char **out) {
    if (mat == NULL) {return ERNULL;}
    free(mat->data);
    mat->data = NULL;
    return SUCCESS;
}
