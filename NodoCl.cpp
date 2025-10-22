#include "NodoCl.h"

NodoCl::NodoCl() : dato(nullptr), sig(nullptr) {}
NodoCl::NodoCl(Cliente* c) : dato(c), sig(nullptr) {}
NodoCl::~NodoCl() {}

Cliente* NodoCl::getDato() { return dato; }
NodoCl* NodoCl::getSig() { return sig; }
void NodoCl::setDato(Cliente* c) { dato = c; }
void NodoCl::setSig(NodoCl* s) { sig = s; }
