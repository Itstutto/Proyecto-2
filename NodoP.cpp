#include "NodoP.h"
NodoP::NodoP()
{
	dato = nullptr;
	sig = nullptr;
}
NodoP::NodoP(Persona* p)
{
	dato = p;
	sig = nullptr;
}
NodoP::~NodoP() {}
Persona* NodoP::getDato() { return dato; }
NodoP* NodoP::getSiguiente() { return sig; }
void NodoP::setDato(Persona* p) { dato = p; }
void NodoP::setSiguiente(NodoP* s) { sig = s; }

