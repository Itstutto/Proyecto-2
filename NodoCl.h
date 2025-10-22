#pragma once
#include "Cliente.h"

class NodoCl {
private:
	Cliente* dato;
	NodoCl* sig;
public:
	NodoCl();
	NodoCl(Cliente* c);
	~NodoCl();

	Cliente* getDato();
	NodoCl* getSig();
	void setDato(Cliente* c);
	void setSig(NodoCl* s);
};
