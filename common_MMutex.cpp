/*
 * MMutex.cpp
 *
 *  Created on: Apr 24, 2009
 *      Author: mmmary
 */
#include <iostream>

#include "common_MMutex.h"

MMutex::MMutex() {
	pthread_mutex_init(&mutex, NULL);
}

int MMutex::lock(){
	pthread_mutex_lock(&mutex);
		return 0;
}
	int MMutex::unlock(){

		return  pthread_mutex_unlock(&mutex);
	}


MMutex::~MMutex() {
	pthread_mutex_destroy(&mutex);
}
