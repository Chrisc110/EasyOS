#ifndef EOS_THREAD_H_
#define EOS_THREAD_H_

#include <stdint.h>

typedef enum {
	HIGHEST_PRIORITY = 0,
	BELOW_HIGHEST_PRIORITY,
	MEDIUM_PRIORITY,
	BELOW_MEDIUM_PRIORITY,
	LOW_PRIORITY,
	LOWEST_PRIORITY
} EOStaskPriority_e;

typedef enum {
	RUNNING,
	READY,
	WAITING,
	SLEEPING
} EOStaskState_e;

typedef struct EOSthread_t {
	void (*funct_ptr)();
	uint32_t * stackPtrAddr;
	EOStaskPriority_e priority;
	uint32_t delay;
	struct EOSthread * next;
}EOSthread_t;

typedef struct {
	EOSthread_t * runningThread;
	uint8_t threadCount;
	uint32_t sysCount;
	EOSthread_t * priorityArray[6];
	EOSthread_t * sleepingHead;
	uint32_t * initialMSP;
	//mutexHead
	//semaphoreHead

}EOSstatus_t;

void EOScreateThread (void (*funct_ptr)(), EOStaskPriority_e priority);


#endif /* EOS_THREAD_H_ */
