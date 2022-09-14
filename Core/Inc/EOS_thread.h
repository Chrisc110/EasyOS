#ifndef EOS_THREAD_H_
#define EOS_THREAD_H_

typedef enum {
	HIGHEST_PRIORITY = 0,
	BELOW_HIGHEST_PRIORITY,
	MEDIUM_PRIORITY,
	BELOW_MEDIUM_PRIORITY,
	LOW_PRIORITY,
	LOWEST_PRIORITY
} EOStaskPriority;

typedef enum {
	RUNNING,
	READY,
	WAITING,
	SLEEPING
} EOStaskState;

typedef struct EOSthread {

};
#endif /* EOS_THREAD_H_ */
