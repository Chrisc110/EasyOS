#include "cmsis_os2.h"                  // ::CMSIS:RTOS2
#include "cmsis_compiler.h"             // Compiler agnostic definitions

#include <stddef.h>
#include "EOS_kernel.h"

#define DEFAULT_STACK_SIZE      512

typedef struct {

    // Ensure first element of struct is stack pointer
    uint32_t *stackPointer;

} eTCB;

osThreadId_t eCreateThread (osThreadFunc_t func, void *argument, const osThreadAttr_t *attr) {

    eTCB* newThread = eMalloc(sizeof(eTCB));

    uint32_t *stackPointer = eMalloc(DEFAULT_STACK_SIZE);


    *stackPointer = 1<<24;

    --stackPointer;
    *stackPointer = (uint32_t)func;

    for (int i = 0; i < 14; ++i) {
        --stackPointer;
        *stackPointer = 0x9F - i;
    }

    newThread->stackPointer = stackPointer;

    return (osThreadId_t)newThread;

}
