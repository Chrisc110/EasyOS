#include "EOS_thread.h"
#include "cmsis_os2.h"

eTCB *threadArr[10];
uint32_t * initMSP;
uint8_t threadCount = 0;
uint8_t threadIndex = 0;
uint8_t counter = 0;

static int easyHeap[5000];
uint32_t heapIndex = 5000-1;

void contextSwitch(void)
{
	volatile uint32_t *icsr = (void*)0xE000ED04; //Interrupt Control/Status Vector
	*icsr = 0x1<<28; //tell the chip to do the pendsv by writing 1 to the PDNSVSET bit

	//flush things
	__asm("isb"); //This just prevents other things in the pipeline from running before we return

	return;
}

osThreadId_t osThreadNew (osThreadFunc_t func, void *argument, const osThreadAttr_t *attr)
{
	eTCB * newThread = (eTCB*)&easyHeap[heapIndex];
	heapIndex -= sizeof(eTCB);
	threadArr[threadCount] = newThread;
	threadCount++;
	//newThread->stackPointer = initMSP - THREAD_STACK_SIZE * threadCount;
	newThread->stackPointer = (uint32_t*)&easyHeap[heapIndex];
	heapIndex -= THREAD_STACK_SIZE;

	*(newThread->stackPointer) = 1<<24;
	(newThread->stackPointer)--;

	*(newThread->stackPointer) = (uint32_t)(func);
	(newThread->stackPointer)--;

	*(newThread->stackPointer) = 0xE;
	newThread->stackPointer--;

	*newThread->stackPointer = 0xD;
	newThread->stackPointer--;

	*newThread->stackPointer = 0xC;
	newThread->stackPointer--;

	*newThread->stackPointer = 0xB;
	newThread->stackPointer--;

	*newThread->stackPointer = 0xA;
	newThread->stackPointer--;

	*newThread->stackPointer = 0x9;
	newThread->stackPointer--;

	*newThread->stackPointer = 0xB;
	newThread->stackPointer--;

	*newThread->stackPointer = 0xA;
	newThread->stackPointer--;

	*newThread->stackPointer = 0x9;
	newThread->stackPointer--;

	*newThread->stackPointer = 0x8;
	newThread->stackPointer--;

	*newThread->stackPointer = 0x7;
	newThread->stackPointer--;

	*newThread->stackPointer = 0x6;
	newThread->stackPointer--;

	*newThread->stackPointer = 0x5;
	newThread->stackPointer--;

	*newThread->stackPointer = 0x4;


	return NULL;
}

osStatus_t osKernelInitialize(void) {

//    memset(eHepa, HEAP_INITIAL, HEAP_SIZE);
    *(uint32_t volatile *)0xE000ED20 |= (0xFFU << 16);

    initMSP = (uint32_t*)0;

    return osOK;

}

osStatus_t osKernelStart(void) {

    __set_CONTROL(1<<1);
    __set_PSP((uint32_t)(threadArr[threadIndex]->stackPointer) + 14*4);

    contextSwitch();

    return osOK;

}

void setNewPSP(void){
	threadArr[threadIndex]->stackPointer = (uint32_t*)__get_PSP();

	threadIndex = (threadIndex + 1) % threadCount;
	if (threadIndex == 0)
	{
	    threadIndex = 1;
	}
	printf("thread count: %i\n\r", threadIndex);
	printf("Counter: %i\n\r", counter);
	counter++;


	__set_PSP((uint32_t)(threadArr[threadIndex]->stackPointer));
}
