/*
 * ServidorEx.h
 *
 *  Created on: May 17, 2009
 *      Author: mmmary
 */

#ifndef SERVIDOREX_H_
#define SERVIDOREX_H_
#include "server_Servidor.h"
#include "common_MSocket.h"

class ServidorEx : public MThread{
private:
	Servidor* servidor;
	MSocket* socket;
public:

	ServidorEx(Servidor* servidor);
	void* run();
	virtual ~ServidorEx();
};

#endif /* SERVIDOREX_H_ */
