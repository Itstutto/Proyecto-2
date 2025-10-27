#include "NodoSolicitud.h"

NodoSolicitud::NodoSolicitud() : dato(nullptr), sig(nullptr) {}

NodoSolicitud::NodoSolicitud(SolicitudAlquiler* d) : dato(d), sig(nullptr) {}

NodoSolicitud::~NodoSolicitud() {}

SolicitudAlquiler* NodoSolicitud::getDato() { return dato; }

NodoSolicitud* NodoSolicitud::getSig() { return sig; }

void NodoSolicitud::setDato(SolicitudAlquiler* d) { dato = d; }

void NodoSolicitud::setSig(NodoSolicitud* s) { sig = s; }
