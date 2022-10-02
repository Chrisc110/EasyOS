#ifndef EOS_THREAD_H_
#define EOS_THREAD_H_

#include <stdint.h>
#include "stm32g4xx.h"


#define THREAD_STACK_SIZE 0x200 //512 byte thread stack. This is a lot.

typedef struct{
    void (*funct_ptr)();
    uint32_t stackPtr_address;
}CBOS_threadInfo_t;

typedef struct {
    uint8_t thread_count;
    uint8_t current_thread;
    uint32_t initial_MSP_addr;
    CBOS_threadInfo_t threadInfo[10];
}CBOS_status_t;


void CBOS_create_thread(void (*funct_ptr)());

void trigger_pendsv(void);

void idle_thread(void);

void CBOS_kernel_initialize(void);

void CBOS_kernel_start(void);

extern CBOS_status_t CBOS_threadStatus;

void set_PSP_new_stackPtr(void);

#endif /* EOS_THREAD_H_ */
