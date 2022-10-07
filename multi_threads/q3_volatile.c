#include <threads.h>
#include <stdio.h>
#include <stdatomic.h>

#if !defined(__STDC_NO_ATOMICS__)
atomic_int x = 0, y = 0;
#endif
// case：指令重排
int run(void* v) {
    x = 10;
    y = 20; // ！变量 y 的值可能被优先更新！
}
int observe(void* v) {
    while (y != 20); // 忙等待；退出时 y=20
    printf("%d\n", x); // 只在 x 被更新后打印；
}
int main(void) {
#if !defined(__STDC_NO_THREADS__)
    thrd_t threadA, threadB;
    thrd_create(&threadA, run, NULL);
    thrd_create(&threadB, observe, NULL);
    thrd_join(threadA, NULL);
    thrd_join(threadB, NULL);
#endif
    return 0;
}