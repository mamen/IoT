//#include "scheduler.h"
//
//
//uint8_t scheduler_startThread(void* (*func)()) {
//
////    Thread *t = malloc(sizeof(Thread));
////
////    t->threadID = getThreadID();
////
////    if(t->threadID == THREAD_ID_INVALID) {
////        return -1;
////    }
////
////    t->state = THREAD_READY;
////    t->threadFunc = func;
////
////    if(setjmp(t->context) == 0) {
////        return t->threadID;
////    } else {
////        threadList[currentRunningThread]->threadFunc(currentRunningThread);
////        scheduler_killThread();
////        return THREAD_ID_INVALID;
////    }
//
//    return 0;
//}
