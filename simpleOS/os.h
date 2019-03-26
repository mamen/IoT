#ifndef OS_H_
#define OS_H_

#include <inttypes.h>
#include <setjmp.h>

#define MAX_THREADS 10

typedef enum State {
    THREAD_READY,
    THREAD_RUNNING
} State_t;

typedef struct {
    uint16_t stack;
    jmp_buf context;
    State_t state;

    void(*func)();
} Thread_t;

Thread_t threads[MAX_THREADS];
int thread_counter = 0;
Thread_t* running = 0;

void ATOMIC_START(void);
void ATOMIC_END(void);

void os_createThread(void(*action)(Thread_t*));
Thread_t* os_round_robin(void);
void os_change_thread(Thread_t* thread);
void os_start();

#endif
