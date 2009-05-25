/*
 * MMutex.h
 *
 *  Created on: Apr 24, 2009
 *      Author: mmmary
 */

/*Clase que sirve para detener la ejacucion de un pthread
 * */

#ifndef MMUTEX_H_
#define MMUTEX_H_
#include <pthread.h>


class MMutex {
private:
	pthread_mutex_t mutex;

public:
	MMutex();
	int lock();
	int unlock();
	virtual ~MMutex();
};

#endif /* MMUTEX_H_ */
