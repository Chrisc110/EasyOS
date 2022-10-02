#ifndef INC_EOS_THREAD_H_
#define INC_EOS_THREAD_H_

osThreadId_t eCreateThread (osThreadFunc_t func, void *argument, const osThreadAttr_t *attr);

#endif /* INC_EOS_THREAD_H_ */
