#include "os.h"

void os_create_thread(void(*tFunc)(), uint16_t sp) {
    ATOMIC_START();
    if ( thread_counter < MAX_THREADS ) {
        Thread_t* t = &threads[thread_counter];
        t->func = tFunc;
        t->state = THREAD_READY;
        t->stack = sp;

        ++thread_counter;

        if ( setjmp(t->context) == 0) {
            ATOMIC_END();
            return;
        } else {
            _set_SP_register(t->stack);
            ATOMIC_END();
            t->func();
            return;
        }
    }
    ATOMIC_END();
}

Thread_t* os_round_robin(void) {
    ATOMIC_START();
    if ( thread_counter == 0 ) {
        ATOMIC_END();
        return 0;
    }

    static int current = 0;
    if ( current >= thread_counter ) {
        current = 0;
    }

    ATOMIC_END();
    return &threads[current++];
}

void os_change_thread(Thread_t* thread) {
    ATOMIC_START();
    switch ( thread->state ) {
    case THREAD_RUNNING:
        break;
    case THREAD_READY:
        // Start the thread
        if ( running && running->state == THREAD_RUNNING ) {
            if ( setjmp(running->context) == 0) {
                // End the old thread
                running->state = THREAD_READY;

                thread->state = THREAD_RUNNING;
                running = thread;

                ATOMIC_END();
                longjmp(running->context, 1);
            }
        }

        break;
    }
    ATOMIC_END();
}

void os_start() {
    ATOMIC_START();
    Thread_t* t = os_round_robin();
    if ( t != 0 ) {
        running = t;
        running->state = THREAD_RUNNING;

        ATOMIC_END();
        longjmp(running->context, 1);
    }
    ATOMIC_END();
}
