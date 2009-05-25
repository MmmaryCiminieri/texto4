/*
 * Lock.h
 *
 *  Created on: Apr 24, 2009
 *      Author: mmmary
 */

/* Clase utilitaria para "lockear" un mutex
  */
#ifndef LOCK_H_
#define LOCK_H_

#include "common_MMutex.h"

class Lock {
private:
	MMutex& mutex;
public:
	Lock(MMutex& m);

	virtual ~Lock();
};

#endif /* LOCK_H_ */
