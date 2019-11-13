#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

int cnt = 0;
#define NUM_THREAD 100

void* thr_main(void* arg){
    cnt++;
    sleep(1);
    return ((void*)1);
}

int main(void){
    int err, i;
    pthread_t tid[NUM_THREAD];
    void* ret;

    for(i = 0; i < NUM_THREAD; i++){
        if(pthread_create(&tid[i], NULL, thr_main, NULL)) exit(1);
    }

    for(i = 0; i < NUM_THREAD; i++){
        if(pthread_join(tid[i], &ret)) exit(2);
    }

    printf("done %d\n", cnt);
    return 0;
}
