#include "NodoSuc.h"
NodoSuc::NodoSuc()
{
	dato = nullptr;
	sig = nullptr;
}
NodoSuc::NodoSuc(Sucursal* s)
{
	dato = s;
	sig = nullptr;
}
NodoSuc::~NodoSuc() {}
Sucursal* NodoSuc::getDato() { return dato; }
NodoSuc* NodoSuc::getSig() { return sig; }
void NodoSuc::setDato(Sucursal* s) { dato = s; }
void NodoSuc::setSig(NodoSuc* s) { sig = s; }

