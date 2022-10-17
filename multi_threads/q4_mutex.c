#include <threads.h>
#include <stdio.h>
#define THREAD_COUNT 10
#define THREAD_LOOP 10000
mtx_t mutex;
long counter = 0;
int run(void* data) {
    for (int i = 0; i < THREAD_LOOP; i++) {
        mtx_lock(&mutex); // 对互斥量加锁，
        counter++;
        mtx_unlock(&mutex); // 释放一个互斥量；
    }
    printf("Thread %d terminates.\n", *((int*)data));
    return thrd_success;
}
int main(void) {
#ifndef __STDC_NO_THREADS__
    int ids[THREAD_COUNT];
    mtx_init(&mutex, mtx_plain); // 创建一个简单、非递归的互斥量对象；
    thrd_t threads[THREAD_COUNT];
    for (int i = 0; i < THREAD_COUNT; i++) {
        ids[i] = i + 1;
        thrd_create(&threads[i], run, ids + i);
    }
    for (int i = 0; i < THREAD_COUNT; i++)
        thrd_join(threads[i], NULL);
    printf("Counter value is: %ld.\n", counter);
    mtx_destroy(&mutex); // 销毁一个互斥量对象；
#endif
    return 0;
}

/**
Thread 1 terminates.
Thread 2 terminates.
Thread 6 terminates.
Thread 9 terminates.
Thread 8 terminates.
Thread 7 terminates.
Thread 3 terminates.
Thread 10 terminates.
Thread 4 terminates.
Thread 5 terminates.
Counter value is: 100000.
 */