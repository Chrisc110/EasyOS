#include "cmsis_os2.h"
#include "EOS_kernel.h"

#include <stdint.h>

#define HEAP_INITIAL    69
#define HEAP_SIZE       (1<<14)

static uint8_t eHeap[HEAP_SIZE];

uint8_t numThreads;

osStatus_t osKernelInitialize(void) {

//    memset(eHepa, HEAP_INITIAL, HEAP_SIZE);

    return osOK;

}

osStatus_t osKernelStart(void) {

    return osOK;

}
