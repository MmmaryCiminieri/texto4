/*
 * Listaa.h
 *
 *  Created on: Apr 3, 2009
 *      Author: mmmary
 */

/* Clase utilitaria que sirve para recorrer guardar
 * elementos  de tipo T
 */
#ifndef LISTA_H_
#define LISTA_H_

#include "common_Nodo.h"
#include "common_Iterador.h"

#include <iostream>
#include <stdlib.h>

template<typename T> class Lista {

private:

	Nodo<T>* primero;
	int tamaniio;

public:

	Lista() {
		this->primero = NULL;
		this->tamaniio = 0;
	}

	virtual ~Lista() {
		Nodo<T>* nodoABorrar = this->primero;
		while (nodoABorrar != NULL) {
			Nodo<T>* siguiente = nodoABorrar->getNext();
			delete nodoABorrar;
			nodoABorrar = siguiente;
		}
		this->tamaniio = 0;

	}

	void add(T data) {
		Nodo<T>* anterior;
		Nodo<T>* nodoNuevo = new Nodo<T> (data);

		anterior = (this->primero);
		if (this->primero == NULL) {
			this->primero = nodoNuevo;
		} else {
			while (anterior->hasNext()) {
				anterior = anterior->getNext();
			}

			anterior->setNext(nodoNuevo);
		}
		this->tamaniio++;
	}

	/*Requiere que los objetos tengan definido los operadores > y <*/
	void addOrdenada(T data) {

		Nodo<T>* anterior;
		Nodo<T>* anteriorAnterior;
		Nodo<T>* nodoNuevo = new Nodo<T> (data);

		anterior = (this->primero);
		anteriorAnterior = NULL;
		if (this->primero == NULL) {
			this->primero = nodoNuevo;
		} else {
			while (anterior->hasNext() && (data > (anterior->getData()))) {
				anteriorAnterior = anterior;
				anterior = anterior->getNext();
			}
			if (anterior->hasNext()) {
				/*Existe un dato mas grande que el actual*/
				if (anteriorAnterior == NULL) {
					this->primero = nodoNuevo;
				} else {
					anteriorAnterior->setNext(nodoNuevo);
				}
				nodoNuevo->setNext(anterior);

			} else {
				if (data > anterior->getData()) {
					anterior->setNext(nodoNuevo);
				} else {
					anteriorAnterior->setNext(nodoNuevo);

					nodoNuevo->setNext(anterior);
				}
			}
		}
		this->tamaniio++;
	}

	bool isEmpty() const {
		return (this->primero == NULL);
	}

	Nodo<T>* getFirst() {
		return this->primero;
	}

	int count() const {
		return this->tamaniio;
	}

	Iterador<T> iterador() {
		Iterador<T> it(this->primero);
		return it;
	}
	/*anda bien para listas de punteros para objetos  redefin'i el == y el != */
	bool isThere(T data) {

		T dataAux;
		Iterador<T> it = this->iterator();

		while (it.hasNext()) {
			dataAux = it.next();
			if (dataAux == data) {
				return true;
			}
		}
		return false;
	}

	/* false si no lo encuentra, true si lo logro borrar*/
	/*borra la primer ocurrencia de data */
	bool remove(T data) {

		Nodo<T>* actual = this->primero;
		Nodo<T>* anterior= NULL;

		while ((actual != NULL) && (actual->getData() != data)) {
			anterior = actual;
			actual = actual->getNext();

		}

		if (actual == NULL) {
			return false;
		}
		Nodo<T>* next = actual->getNext();

		if (actual == this->primero) {

			delete (this->primero);
			this->primero = next;

		} else {
			delete (actual);
			anterior->setNext(next);

		}
		this->tamaniio--;
		return true;

	}

};

#endif /* LIST_H_ */

