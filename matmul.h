#ifndef MAT_MUL
#define MAT_MUL

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
/*
 * @des : custom error messages and error handling
 */
typedef enum {
    SUCCESS, ERSIZE, ERNULL, ERSHAPE
} mat_status;

/*
 * @des : a matrix is implemented using a float array with <width> and <height>;
 *        <stride> store the underlying (or the parent structs)
 *        number of column per row 
 */
typedef struct {
    size_t width;
    size_t height;
    float  *data;
} matrix;

/* 
 * @des    : initiate a matrix from the given <float array>
 * @return : mat_status
 */ 
mat_status mat_init(float *array, size_t array_length, matrix *mat, size_t height, size_t width);

/* 
 * @des    : initiate a matrix from the given <float array>
 * @return : return a <pointer> to the initiated matrix
 *           return <NULL> on failure.
 */ 

mat_status mat_create(matrix *mat, size_t height, size_t width); 

/*
 * @WARN: unsafe indexing, using AdressSanitizer is recommended
 * @des : return the 2D representation of matrix <mat>
 *        this can then be used with indexer operator "[]"
 */
#define index(mat) ((float (*)[(mat)->stride]) (mat)->data)

/*
 * @des : return the index at [<row>][<col>] in the matrix <mat>
 */
#define sindex(mat, row, col) (*mat_safe((mat), (row), (col)))

/* 
 * @des    : to be used with sindex macro, check if the
 *           inputs are valid
 * @return : return a <ptr> to the index at [<row>][<col>]
 */
static inline float* mat_safe(matrix *mat, size_t row, size_t col);

/*
 * @des : return the index at [<row>][<col>] in the matrix <mat>
 *        to be use for <const matrix> only   
 */
#define const_sindex(mat, row, col) (*mat_safe_const((mat), (row), (col)))

/* 
 * @des    : to be used with const_sindex macro, check
 *           if the inputs are valid
 * @return : return a ptr to the index at [<row>][<col>]
 */ 
static inline float* mat_safe_const(const matrix *mat, size_t row, size_t col);

/* 
 * @des    : compute the result of adding <mat1> and <mat2>, write the
 *           result to <ptr>
 * @return : mat_status
 */ 
mat_status mat_add(const matrix *restrict mat1, const matrix *restrict mat2, matrix *restrict ptr);

/* 
 * @des    : compute the result of subtracting <mat1> and <mat2>, write the
 *           result to <ptr>
 * @return : mat_status
 */ 
mat_status mat_sub(const matrix *restrict mat1, const matrix *restrict mat2, matrix *restrict ptr);

/* 
 * @des    : compute the result of multiplying <mat1> and <mat2>, write the
 *           result to <ptr>
 * @return : mat_status
 */ 
mat_status mat_dot(const matrix *restrict mat1, const matrix *restrict mat2, matrix *restrict ptr);

/* 
 * @des    : compute the result of multiplying <mat> to 1 <scalar>, write the
 *           result to <ptr>
 * @return : mat_status
 */ 
mat_status mat_scale(const matrix *restrict mat, float scalar, matrix *restrict ptr);

/* 
 * @des    : format a <matrix> to a printable <string>, store the
 *           result in <ptr>
 * @return : mat_status
 */ 
mat_status mat_str(matrix *mat, char *ptr);

/* 
 * @des    : free the given matrix's memory
 * @return : return 0 on success, -1 on failure
 */ 
mat_status free_mat(matrix *matrix);

#endif
