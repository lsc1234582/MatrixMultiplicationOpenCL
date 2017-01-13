#include "mat.h"
#include <stdio.h>

int main() {
    float mat[16], vec[4], result[4];
    int i;
    // Initialise mat and vec
    for (i = 0; i < 16; ++i) {
        mat[i] = i * 2.0f;
    }
    for (i = 0; i < 4; ++i) {
        vec[i] = i * 3.0f;
    }

    mat4_mult(mat, vec, result);

    print_mat(mat, 4, 4, 1);
    printf("\n");
    printf("\n");
    print_mat(vec, 4, 1, 1);
    printf("\n");
    printf("\n");
    print_mat(result, 4, 1, -1);
    printf("\n");

    return 0;
}
