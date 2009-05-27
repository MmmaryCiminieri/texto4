/*
 * Lock.cpp
 *
 *  Created on: Apr 24, 2009
 *      Author: mmmary
 */
#include <iostream>
#include "common_Lock.h"

Lock::Lock(MMutex& m) : mutex(m) {
	mutex.lock();
}

Lock::~Lock() {
	mutex.unlock();
}
