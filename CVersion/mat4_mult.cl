__kernel void mat4_mult(__global float4* mat1,
                          __global float4* mat2,
                          __global int* res_col,
                          __global float* result) {
    int i = get_global_id(0);
    int j = get_global_id(1);
    result[i* *res_col + j] = dot(mat1[i], mat2[j]);
}
