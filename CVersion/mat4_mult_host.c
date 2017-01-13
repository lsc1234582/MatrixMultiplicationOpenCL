// TODO: Extends to matrix-matrix multiplication
// TODO: Extends to general matrix multiplication
#define PROGRAM_FILE "mat4_mult.cl"
#define KERNEL_FUNC "matvec_mult"

#include "mat.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#ifdef MAC
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif

int mat4_mult(const float *mat1, const float *mat2, float *res) {
    cl_platform_id platform;
    cl_device_id device;
    cl_context context;
    cl_command_queue queue;
    cl_int err;

    cl_program program;
    // A structure containing info about a file. <stdio.h>
    FILE *program_handle;
    char *program_buffer, *program_log;
    size_t program_size;
    cl_kernel kernel;
    size_t work_units_per_kernel;

    cl_mem mat1_buff, mat2_buff, res_buff;
    
    /*
     * Set platform & device & context
     */
    // Get the first platform
    clGetPlatformIDs(1, &platform, NULL);
    // Get the first GPU device
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
    // Create a context containing one device.
    // * Can also create a context from a device type. But not of interest
    // here.
    // * Contexts have more to do with graphics (OpenGL/DirectX)
    context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);

    /*
     * Read program file
     */
    program_handle = fopen(PROGRAM_FILE, "r");
    // fseek(FILE, offset, origin)
    // Sets current position indicator to a new position
    fseek(program_handle, 0, SEEK_END);
    // Returns current value of position indicator
    program_size = ftell(program_handle);
    rewind(program_handle);
    program_buffer = (char*) malloc(program_size +1);
    program_buffer[program_size] = '\0';
    fread(program_buffer, sizeof(char), program_size, program_handle);
    fclose(program_handle);

    /*
     * Compile program
     */
    program = clCreateProgramWithSource(context, 1,
            (const char **)&program_buffer, &program_size, &err);
    free(program_buffer);
    const char options[] = "-cl-std=CL1.2 -Werror";
    err = clBuildProgram(program, 1, &device, options, NULL, NULL);
    if (err < 0) {
        size_t log_size;
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG,
                0, NULL, &log_size);
        program_log = (char*) calloc(log_size + 1, sizeof(char));
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG,
                log_size + 1, program_log, NULL);
        perror("Program failes to build;");
        printf("%s\n", program_log);
        free(program_log);
        clReleaseProgram(program);
        clReleaseContext(context);
        return(-1);
    }

    /*
     * Create kernal and command queue
     */
    kernel = clCreateKernel(program, KERNEL_FUNC, &err);
    queue = clCreateCommandQueue(context, device, 0, &err);

    mat1_buff = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
            sizeof(float)*16, (void *) mat1, &err);
    mat2_buff = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
            sizeof(float)*4, (void *) mat2, &err);
    res_buff = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
            sizeof(float)*4, (void *) res, &err);

    /* Set kernel arguments */
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &mat1_buff);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &mat2_buff);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &res_buff);

    /* Execute kernel */
    work_units_per_kernel = 4;
    clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &work_units_per_kernel, 
            NULL, 0, NULL, NULL);
    
    clEnqueueReadBuffer(queue, res_buff, CL_TRUE, 0, sizeof(float)*4, res,
            0, NULL, NULL);

    clReleaseMemObject(mat1_buff);
    clReleaseMemObject(mat2_buff);
    clReleaseMemObject(res_buff);
    clReleaseKernel(kernel);
    clReleaseCommandQueue(queue);
    clReleaseProgram(program);
    clReleaseContext(context);

    return 0;
}

// orient: 1: horizontal, -1: veritcal
// PRE: Row * Col = size(mat)
void print_mat(const float *mat, size_t row, size_t col, int orient) {
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            size_t index = orient == 1 ? (i * col + j) : (j * row + i);
            printf("%.3f\t", mat[index]);
        }
        if (i != row - 1) printf("\n");
    }
}
