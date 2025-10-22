#pragma once
#include "Colaborador.h"

class NodoCol {
private:
	Colaborador* dato;
	NodoCol* sig;
public:
	NodoCol();
	NodoCol(Colaborador* c);
	~NodoCol();

	Colaborador* getDato();
	NodoCol* getSig();
	void setDato(Colaborador* c);
	void setSig(NodoCol* s);
};
