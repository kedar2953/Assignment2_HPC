#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

// Function to perform vector-scalar addition sequentially
void vector_scalar_addition_sequential(float *v, float scalar, float *result, int size) {
    for (int i = 0; i < size; i++) {
        result[i] = v[i] + scalar;
    }
}

// Function to perform vector-scalar addition in parallel using OpenMP
void vector_scalar_addition_parallel(float *v, float scalar, float *result, int size) {
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        result[i] = v[i] + scalar;
    }
}

int main() {
    int size = 1000000; // Example size
    float scalar = 5.0;
    float *v = (float*)malloc(size * sizeof(float));
    float *result_seq = (float*)malloc(size * sizeof(float));
    float *result_par = (float*)malloc(size * sizeof(float));
    
    // Initialize vector
    for (int i = 0; i < size; i++) {
        v[i] = (float)(rand() % 100);
    }
    
    // Sequential execution
    double start = omp_get_wtime();
    vector_scalar_addition_sequential(v, scalar, result_seq, size);
    double end = omp_get_wtime();
    printf("Sequential Time: %f seconds\n", end - start);

    // Parallel execution
    start = omp_get_wtime();
    vector_scalar_addition_parallel(v, scalar, result_par, size);
    end = omp_get_wtime();
    printf("Parallel Time: %f seconds\n", end - start);

    // Free allocated memory
    free(v);
    free(result_seq);
    free(result_par);

    return 0;
}
