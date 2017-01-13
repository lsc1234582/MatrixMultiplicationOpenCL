#include "mat.h"
#include <stdio.h>

int main() {
    float mat1[4], mat2[12], result[3];
    int i;
    // Initialise mat1 and mat2
    for (i = 0; i < 4; ++i) {
        mat1[i] = i * 2.0f;
    }
    for (i = 0; i < 12; ++i) {
        mat2[i] = i * 3.0f;
    }

    mat4_mult(mat1, mat2, 14, 43, result);

    print_mat(mat1, 1, 4, 1);
    printf("\n");
    printf("\n");
    print_mat(mat2, 4, 3, -1);
    printf("\n");
    printf("\n");
    print_mat(result, 4, 3, -1);
    printf("\n");

    return 0;
}
