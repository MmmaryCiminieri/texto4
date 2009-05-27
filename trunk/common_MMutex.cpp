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

void MMutex::lock(){
	pthread_mutex_lock(&mutex);

}

void MMutex::unlock(){

  pthread_mutex_unlock(&mutex);
	}


MMutex::~MMutex() {
	pthread_mutex_destroy(&mutex);
}
