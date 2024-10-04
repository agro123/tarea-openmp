#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int arrPositions = 100;
    int Array[arrPositions]; // Use rand() % 10000 for init
    int max = 0;
    int min = 100000;
    int avg = 0;
    
    srand(time(NULL));

    #pragma omp parallel for
    for (int i = 0; i < arrPositions; i++) {
        Array[i] = rand() % 10000;
    }

    #pragma omp parallel for reduction(+:avg) reduction(max:max) reduction(min:min)
    for (int i = 0; i < arrPositions; i++)
    {
        int threadNum = omp_get_thread_num();
        int value = Array[i];
        if(value >= max){
            max = value;
        }
        if(value <= min){ 
            min = value;
        }
        avg += value;
        printf(" Thread %d: value %d in index %d\n", threadNum, value, i);
    }
    printf("------------- END parallel zone-----------\n");
    avg = avg/arrPositions;

    printf("Max is %d,\n", max);
    printf("Min is %d,\n", min);
    printf("Average is %d\n", avg);

    int rmax = 0;
    int rmin = 100000;
    double ravg = 0;
    for (int i = 0; i < arrPositions; i++) {
        int value = Array[i];
        if(value <= rmin){ 
            rmin = value;
        }
        if(value >= rmax){
            rmax = value;
        }
        ravg += value;
    }
    printf("Real Max is %d,\n", rmax);
    printf("Real Min is %d,\n", rmin);
    printf("Real Average is %.2f\n", ravg/arrPositions);
    return 0;
}