#ifndef MAT_H
#define MAT_H
/*
 * Some custom GPU-enabled (OpenCL) matrix oparations
 */
#include <sys/types.h>

int mat4_mult(const float *mat1, const float *mat2, const size_t dim1,
        const size_t dim2, float *res);

void print_mat(const float *mat, size_t row, size_t col, int orient);

#endif
