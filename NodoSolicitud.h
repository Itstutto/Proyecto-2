#pragma once
#include "SolicitudAlquiler.h"

class NodoSolicitud {
private:
    SolicitudAlquiler* dato;
    NodoSolicitud* sig;
public:
    NodoSolicitud();
    NodoSolicitud(SolicitudAlquiler* d);
    ~NodoSolicitud();
    SolicitudAlquiler* getDato();
    NodoSolicitud* getSig();
    void setDato(SolicitudAlquiler* d);
    void setSig(NodoSolicitud* s);
};
