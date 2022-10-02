#ifndef EOS_THREAD_H_
#define EOS_THREAD_H_

#include <stdint.h>
#include "stm32g4xx.h"

#define THREAD_STACK_SIZE 512

typedef struct {
    uint32_t *stackPointer;
} eTCB;

void setNewPSP(void);

void contextSwitch(void);

#endif /* EOS_THREAD_H_ */
