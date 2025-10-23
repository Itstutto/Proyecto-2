#pragma once
#include "Sucursal.h"

class NodoSuc
{
private:
	Sucursal* dato;
	NodoSuc* sig;
public:
	NodoSuc();
	NodoSuc(Sucursal* s);
	~NodoSuc();
	Sucursal* getDato();
	NodoSuc* getSig();
	void setDato(Sucursal* s);
	void setSig(NodoSuc* s);
};

