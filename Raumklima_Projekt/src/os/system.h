#ifndef SRC_OS_SYSTEM_H_
#define SRC_OS_SYSTEM_H_

#include <inttypes.h>
#include "timer.h"
#define __istate_ts unsigned short

void system_systickInit(void);
uint32_t system_getSysticks(void);
void system_sleep(uint32_t millis);

#endif /* SRC_OS_SYSTEM_H_ */
