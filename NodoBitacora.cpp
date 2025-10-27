#include "NodoBitacora.h"

NodoBitacora::NodoBitacora() : dato(nullptr), sig(nullptr) {}

NodoBitacora::NodoBitacora(EstadoBitacora* d) : dato(d), sig(nullptr) {}

NodoBitacora::~NodoBitacora() {}

EstadoBitacora* NodoBitacora::getDato() { return dato; }

NodoBitacora* NodoBitacora::getSig() { return sig; }

void NodoBitacora::setDato(EstadoBitacora* d) { dato = d; }

void NodoBitacora::setSig(NodoBitacora* s) { sig = s; }
