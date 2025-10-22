#include "NodoCol.h"

NodoCol::NodoCol() : dato(nullptr), sig(nullptr) {}
NodoCol::NodoCol(Colaborador* c) : dato(c), sig(nullptr) {}
NodoCol::~NodoCol() {}

Colaborador* NodoCol::getDato() { return dato; }
NodoCol* NodoCol::getSig() { return sig; }
void NodoCol::setDato(Colaborador* c) { dato = c; }
void NodoCol::setSig(NodoCol* s) { sig = s; }
