#pragma once
#include "Plantel.h"
class NodoPl
{
private:
	Plantel* dato;
	NodoPl* sig;
public:
	NodoPl();
	NodoPl(Plantel* p);
	Plantel* getDato();
	NodoPl* getSig();
	void setDato(Plantel* p);
	void setSig(NodoPl* s);
};

