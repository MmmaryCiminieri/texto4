/*
 * Queue.h
 *
 *  Created on: Apr 3, 2009
 *      Author: mmmary
 */

/* Clase utilitaria cola de elmentos de tipo T
 */

#ifndef COLA_H_
#define COLA_H_

#include "common_Lista.h"

template<class T> class Cola {

private:
	Lista<T> lista;

public:

	void vaciar() {
		while (!this->isEmpty()) {
			this->pop();
		}
	}

	void push(T data) {
		this->lista.add(data);
	}

	bool isEmpty() {
		return (this->lista.isEmpty());
	}

	int count() const {
		return this->lista.count();
	}

	T pop() {
		Nodo<T>* nodo = this->lista.getFirst();
		T data = nodo->getData();
		this->lista.remove(data);
		return data;
	}

	T peek() {

		T data = this->lista.getFirst()->data;
		return data;
	}

};

#endif /* COLA_H_ */
