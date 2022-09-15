#ifndef EOS_THREAD_H_
#define EOS_THREAD_H_

EOSstatus_t * EOSstatus;

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
	EOStaskPriority priority;
	uint32_t delay;
	struct EOSthread * next;
};

typedef struct {
	EOSthread * runningThread;
	uint8_t threadCount;
	uint32_t sysCount;
	EOSthread * priorityArray[6];
	EOSthread * sleepingHead;
	uint32_t * initialMSP;
	//mutexHead
	//semaphoreHead

}EOSstatus_t;

void EOScreateThread (void (*funct_ptr)(), EOStaskPriority priority);


#endif /* EOS_THREAD_H_ */
