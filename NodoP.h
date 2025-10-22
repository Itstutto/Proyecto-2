#pragma once
#include "Persona.h"
class NodoP
{
private:
	Persona* dato;
	NodoP* sig;
public:
	NodoP();
	NodoP(Persona* p);
	~NodoP();
	Persona* getDato();
	NodoP* getSiguiente();
	void setDato(Persona* p);
	void setSiguiente(NodoP* s);
};

