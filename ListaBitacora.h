#pragma once
#include <string>
#include <sstream>
#include "EstadoBitacora.h"

using namespace std;

class ListaBitacora {
private:
	NodoBitacora* primero;
	NodoBitacora* ultimo;
	int tam;
public:
	ListaBitacora();
	~ListaBitacora();
	NodoBitacora* getPrimero();
	NodoBitacora* getUltimo();
	int getTam();
	bool insertarFinal(EstadoBitacora* e);
	EstadoBitacora* getUltimoEstado();
	string mostrarBitacora();
};
