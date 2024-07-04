#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <time.h>

//functions from the lecture
void* func1(void* arg) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    printf("Inside the first thread\n");
    for (int i = 0; i < 1000000000; i++) {
        //delay
    }
    pthread_t id = pthread_self();
    printf("First thread id %lu\n", (unsigned long) id);
    printf("Finished the first thread\n");

    clock_gettime(CLOCK_MONOTONIC, &end);
    unsigned long long elapsed_ns = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);
    printf("Execution time for the first thread: %llu ns\n\n", elapsed_ns);

    pthread_exit(NULL);
}

void* func2(void* arg) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    printf("Inside the second thread\n");
    
   for (int i = 0; i < 1000000000; i++) {
        //delay
    }
    pthread_t id = pthread_self();
    printf("Second thread id %lu\n", (unsigned long) id);
    printf("Finished the second thread\n");

    clock_gettime(CLOCK_MONOTONIC, &end);
    unsigned long long elapsed_ns = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);
    printf("Execution time for the second thread: %llu ns\n\n", elapsed_ns);

    pthread_exit(NULL);
}

void* func3(void* arg) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    printf("Inside the third thread\n");
   
for (int i = 0; i < 1000000000; i++) {
        //delay
    }
     pthread_t id = pthread_self();
    printf("Third thread id %lu\n", (unsigned long) id);
    printf("Finished the third thread\n");

    clock_gettime(CLOCK_MONOTONIC, &end);
    unsigned long long elapsed_ns = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);
    printf("Execution time for the third thread: %llu ns\n\n", elapsed_ns);

    pthread_exit(NULL);
}

void* func4(void* arg) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    printf("Inside the fourth thread\n\n");
   
 for (int i = 0; i < 1000000000; i++) {
        //delay
    }
     pthread_t id = pthread_self();
    printf("Fourth thread id %lu\n", (unsigned long) id);
    printf("Finished the fourth thread\n");

    clock_gettime(CLOCK_MONOTONIC, &end);
    unsigned long long elapsed_ns = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);
    printf("Execution time for the fourth thread: %llu ns\n\n", elapsed_ns);

    pthread_exit(NULL);
}

int main(){
    pthread_t ptid1;
    pthread_t ptid2;
    pthread_t ptid3;
    pthread_t ptid4;

    cpu_set_t cpuset1;

    CPU_ZERO(&cpuset1);
    CPU_SET(0, &cpuset1); 

   
    pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset1); 
    pthread_attr_t attr;
    pthread_attr_init(&attr);


    pthread_create(&ptid1, NULL, &func1, NULL);
    pthread_create(&ptid2, NULL, &func2, NULL);
    pthread_create(&ptid3, NULL, &func3, NULL);
    pthread_create(&ptid4, NULL, &func4, NULL);

    pthread_setaffinity_np(ptid1, sizeof(cpu_set_t), &cpuset1);
    pthread_setaffinity_np(ptid2, sizeof(cpu_set_t), &cpuset1);
    pthread_setaffinity_np(ptid3, sizeof(cpu_set_t), &cpuset1);
    pthread_setaffinity_np(ptid4, sizeof(cpu_set_t), &cpuset1);
    printf("This line may be printed before thread terminates\n");


    struct sched_param param_other;
    param_other.sched_priority = sched_get_priority_max(SCHED_OTHER);
    pthread_setschedparam(ptid1, SCHED_OTHER, &param_other);
    pthread_setschedparam(ptid2, SCHED_OTHER, &param_other);
    pthread_setschedparam(ptid3, SCHED_OTHER, &param_other);
    pthread_setschedparam(ptid4, SCHED_OTHER, &param_other);

    pthread_join(ptid1, NULL);
    pthread_join(ptid2, NULL);
    pthread_join(ptid3, NULL);
    pthread_join(ptid4, NULL);
    printf("This line will be printed after thread ends\n");
    pthread_exit(NULL);
    return 0;
}