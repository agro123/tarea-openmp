#include <omp.h>
#include <stdio.h>

int main() {
    #pragma omp parallel num_threads(12)
    {
        int threadNum = omp_get_thread_num();
        if(threadNum % 2 == 0){
            printf("This thread is even %d\n", threadNum);
        } else {
            printf("This thread is odd %d\n", threadNum);
        }
        
    }
    return 0;
}