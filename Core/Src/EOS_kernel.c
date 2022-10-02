#include <string.h>
#include <stdio.h>

#include "stm32g4xx.h"

#include "cmsis_os2.h"
#include "EOS_kernel.h"
#include "EOS_thread.h"

#define HEAP_INITIAL    69
#define HEAP_SIZE       (1<<14)

static uint8_t eHeap[HEAP_SIZE];

#define MAX_THREADS     10

osThreadId_t threadList[MAX_THREADS];

static uint8_t currentThread = 0;
//osThreadId_t currentThread;

void* eMalloc(size_t s) {
    static uint32_t heapLoc = HEAP_SIZE - 4;

    void *cLoc = (void *)(eHeap + heapLoc);
    heapLoc -= s;

    return cLoc;
}

void eSwapThread(void) {
    *(uint32_t *)threadList[currentThread] = __get_PSP();

    currentThread = currentThread == 1 ? 2 : 1;

    __set_PSP(*(uint32_t *)threadList[currentThread]);

}

void trigger_pendsv() {
    *((uint32_t*)0xE000ED04) = 1 << 28;

    __ASM("isb");

    return;
}

osStatus_t osKernelInitialize(void) {

    memset(eHeap, HEAP_INITIAL, HEAP_SIZE);

    *(uint32_t volatile *)0xE000ED20 |= (0xFFu << 16);

    return osOK;

}

osThreadId_t osThreadNew (osThreadFunc_t func, void *argument, const osThreadAttr_t *attr) {
    static uint8_t numThreads = 0;

    osThreadId_t newThread = eCreateThread(func, argument, attr);

    threadList[numThreads++] = newThread;

    return newThread;
}

osStatus_t osKernelStart(void) {

    if (!threadList[0]) {
        return osError;
    }

    __set_CONTROL(1<<1);

    currentThread = 0;

    __set_PSP(*(uint32_t *)threadList[currentThread] - 14 * 4);


    trigger_pendsv();

    return osError;

}

osStatus_t osThreadYield() {
	trigger_pendsv();

	printf("Returned to thread\r\n");

	return osOK;
}
