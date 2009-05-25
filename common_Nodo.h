/*
 * Nodo.h
 *
 *  Created on: Apr 3, 2009
 *      Author: mmmary
 */

/* Clase utilitaria para implementar la lista
 */
#ifndef NODO_H_
#define NODO_H_
#include <iostream>

template<typename T> class Nodo {

private:
	T data;
	Nodo<T>* next;

public:

	Nodo(T data) {
		this->data = data;
		this->next = NULL;
	}

	Nodo<T>* getNext() {
		return this->next;

	}
	T getData() {

		return this->data;
	}
	void setData(T data) {

		this->data = data;
	}

	bool hasNext() {

		return (this->next != NULL);

	}
	void setNext(Nodo<T>* nodo) {

		this->next = nodo;
	}

};

#endif /* NODO_H_ */
