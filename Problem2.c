#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define NUM_ITERATIONS 1000000000

// Function to calculate Pi sequentially
double calculate_pi_sequential(int num_iterations) {
    double sum = 0.0;
    for (int i = 0; i < num_iterations; i++) {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1.0) {
            sum += 1.0;
        }
    }
    return (4.0 * sum) / num_iterations;
}

// Function to calculate Pi in parallel using OpenMP
double calculate_pi_parallel(int num_iterations) {
    double sum = 0.0;
    //sum will be shared between threads, each thread will have its own copy of sum and contribute to global sum
    //it specify that sum will be reduced(e.g combined)
    #pragma omp parallel reduction(+:sum)
    {
        //each thread requires unique seed for generating random numbers    
        unsigned int seed = time(NULL) ^ omp_get_thread_num(); //thread number
        #pragma omp for
        for (int i = 0; i < num_iterations; i++) {
            double x = (double)rand_r(&seed) / RAND_MAX;
            double y = (double)rand_r(&seed) / RAND_MAX;
            if (x * x + y * y <= 1.0) {
                sum += 1.0;
            }
        }
    }
    return (4.0 * sum) / num_iterations;
}

int main() {
    
    

    // Pi Calculation Example
    int num_iterations = NUM_ITERATIONS;
    
    // Sequential execution
    double start = omp_get_wtime();
    double pi_seq = calculate_pi_sequential(num_iterations);
    double end = omp_get_wtime();
    printf("Sequential Time for Pi Calculation: %f seconds\n", end - start);
    printf("Sequential Pi: %f\n", pi_seq);

    // Parallel execution
    start = omp_get_wtime();
    double pi_par = calculate_pi_parallel(num_iterations);
    end = omp_get_wtime();
    printf("Parallel Time for Pi Calculation: %f seconds\n", end - start);
    printf("Parallel Pi: %f\n", pi_par);

    return 0;
}
