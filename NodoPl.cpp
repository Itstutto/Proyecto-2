#include "NodoPl.h"

NodoPl::NodoPl()
{
	dato = nullptr;
	sig = nullptr;
}

NodoPl::NodoPl(Plantel* p)
{
	dato = p;
	sig = nullptr;
}
Plantel* NodoPl::getDato()
{
	return dato;
}
NodoPl* NodoPl::getSig()
{
	return sig;
}
void NodoPl::setDato(Plantel* p)
{
	dato = p;
}
void NodoPl::setSig(NodoPl* s)
{
	sig = s;
}

