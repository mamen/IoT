#include <msp430.h>
#include "os.h"


uint8_t getThreadID() {
    int i;
    for(i = 0; i < MAX_THREADS; i++) {
        if(threadList[i] == NULL) {
            threadList[i] = &t;
            return i;
        }
    }

    return THREAD_ID_INVALID;
}

void scheduler_killThread() {

}

uint8_t scheduler_startThread(void* (*func)()) {

    Thread *t = malloc(sizeof(Thread));

    t->threadID = getThreadID();

    if(t->threadID == THREAD_ID_INVALID) {
        return -1;
    }

    t->state = THREAD_READY;
    t->threadFunc = func;

    if(setjmp(threadList[t->threadID].context) == 0) {
        return t->threadID;
    } else {
        threadList[currentRunningThread]->threadFunc(currentRunningThread);
        scheduler_killThread();
        return THREAD_ID_INVALID;
    }
}


void test(uint8_t tID) {
    int a = tID;
    int b = a * 4;
}



/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	

	scheduler_startThread(&test);

	return 0;
}
