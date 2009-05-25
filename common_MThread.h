/*
 * MThread.h
 *
 *  Created on: Apr 24, 2009
 *      Author: mmmary
 */

/* Encapsulamiento de  pthread
 */
#ifndef MTHREAD_H_
#define MTHREAD_H_
#include <pthread.h>

class MThread {


private:
	pthread_t thread;
	static void* startRoutine(void* arg);

public:
	MThread(){};
	int execute();
	void* join();
	virtual void* run() = 0;
	virtual ~MThread(){};
};

#endif /* MTHREAD_H_ */
