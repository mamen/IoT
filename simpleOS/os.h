#ifndef OS_H_
#define OS_H_

#include <setjmp.h>
#include <inttypes.h>

#define THREAD_ID_INVALID -1
#define MAX_THREADS 10

typedef enum {
    THREAD_READY,
    THREAD_RUNNING
} ThreadState;

typedef struct {
    uint8_t threadID;
    jmp_buf context;
    void* (*threadFunc)();
    ThreadState state;
} Thread;


Thread* threadList[MAX_THREADS];
uint8_t currentRunningThread;


uint8_t scheduler_startThread(void* (*threadFunc)());


#endif

