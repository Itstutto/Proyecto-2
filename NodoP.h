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
	NodoP* getSig();
	void setDato(Persona* p);
	void setSig(NodoP* s);
};

