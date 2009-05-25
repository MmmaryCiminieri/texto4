/*
 * Iterador.h
 *
 *  Created on: Apr 3, 2009
 *      Author: mmmary
 */

/* Clase utilitaria que sirve para recorrer listas
 * que contienen elementos T
 */
#ifndef ITERADOR_H_
#define ITERADOR_H_
#include <iostream>
#include  "common_Nodo.h"

template<typename T> class Iterador {
private:
	Nodo<T>* actual;
	Nodo<T>* primero;

public:

	Iterador(Nodo<T>* actual) {
		this->primero = actual;
		this->actual = actual;
	}

	bool hasNext() {
		return (this->actual != NULL);
	}

	T next() {
		T data = this->actual->getData();
		this->actual = this->actual->getNext();
		return data;
	}

	void reset() {
		this->actual = this->primero;
	}
};

#endif /* ITERADOR_H_ */
