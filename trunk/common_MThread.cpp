/*
 * MThread.cpp
 *
 *  Created on: Apr 24, 2009
 *      Author: mmmary
 */

#include "common_MThread.h"
#include <iostream>

void* MThread::startRoutine(void* arg) {
	MThread* p = (MThread*) arg;
	p->run();
	return NULL;
}

int MThread::execute() {
	 std::cout<<"EXECUTE"<<std::endl;

	return pthread_create(&thread, NULL, startRoutine, (void*) this);

}

void* MThread::join() {
	void* r;
	pthread_join(thread, &r);
	return r;

}
