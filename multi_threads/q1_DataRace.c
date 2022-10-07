#include <threads.h>
// #include <pthread.h>
#include <stdio.h>

#define THREAD_COUNT 20
#define THREAD_LOOP 100000000

// case: 数据竞争
long counter = 0; // 全局变量，用来记录线程的累加值；
int run(void* data) {
    for (int i = 0; i < THREAD_LOOP; i++)
        counter++; // 在线程中递增全局变量的值；(非原子-数据竞争)
    printf("Thread %d terminates.\n", *((int*)data));
    return thrd_success;
}
int main(void) {
#ifndef __STDC_NO_THREADS__
    int ids[THREAD_COUNT]; // 用于存放线程序号的数组；
    thrd_t threads[THREAD_COUNT];
    for (int i = 0; i < THREAD_COUNT; i++) {
        ids[i] = i + 1;
        thrd_create(&threads[i], run, ids + i); // 创建 THREAD_COUNT 个线程；
    }
    for (int i = 0; i < THREAD_COUNT; i++)
        thrd_join(threads[i], NULL); // 让当前线程等待其他线程执行完毕；
    printf("Counter value is: %ld.\n", counter); // 输出 counter 变量最终结果；
#endif
    return 0;
}

/**
Thread 18 terminates.
Thread 19 terminates.
Thread 7 terminates.
Thread 20 terminates.
Thread 1 terminates.
Thread 12 terminates.
Thread 9 terminates.
Thread 8 terminates.
Thread 6 terminates.
Thread 14 terminates.
Thread 4 terminates.
Thread 2 terminates.
Thread 10 terminates.
Thread 5 terminates.
Thread 13 terminates.
Thread 11 terminates.
Thread 3 terminates.
Thread 15 terminates.
Thread 17 terminates.
Thread 16 terminates.
Counter value is: 248261713.
 */