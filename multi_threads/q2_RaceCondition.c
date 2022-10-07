#include <threads.h>
#include <stdio.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <time.h>

#define THREAD_COUNT 10

atomic_int accountA = 100000000; // 转出账户初始金额；
atomic_int accountB = 0; // 转入账户初始金额；

// case：竞态条件
/**
竞态条件（Race Condition）

- 是指由于程序中某些事件的发生**时机与顺序不一致**，从而影响程序运行正确性的一种缺陷。在某些情况下，数据竞争的存在可能会导致竞态条件的出现，但两者的出现实际上并没有太多联系（有部分人认为数据竞争是竞态条件的一种，但也有人持反对意见）
- 详细见“*8. 线程同步*”
  - **解决（Java）**：
    - 使用 synchronized 关键字，对 Critical Section（临界区代码） 进行排他性保护。
    - Lock 显式锁
    - 原子变量（Atomic Variables )
 *
 */

int run(void* v) {
    int _amount = *((int*)v); // 线程本地变量：获得当前线程的转移金额；
    for (;;) {
        // 首先判断转出账户金额是否足够，不够则直接退出；
        if (accountA < _amount) return thrd_error;
        atomic_fetch_add(&accountB, _amount); // 将金额累加到转入账户；
        atomic_fetch_sub(&accountA, _amount); // 将金额从转出账户中扣除；
    }
}

int main(void) {
#if !defined(__STDC_NO_THREADS__) && !defined(__STDC_NO_ATOMICS__)
    thrd_t threads[THREAD_COUNT];
    srand(time(NULL));
    for (int i = 0; i < THREAD_COUNT; i++) {
        int amount = rand() % 50; // 为每一个线程生成一个随机转移金额；
        thrd_create(&threads[i], run, &amount);
    }
    for (int i = 0; i < THREAD_COUNT; i++)
        thrd_join(threads[i], NULL);
    printf("A: %d\nB: %d\n", accountA, accountB);
#endif
    return 0;
}

/*
    A: -233
    B: 100000233
*/

