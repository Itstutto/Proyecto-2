#pragma once
#include "EstadoBitacora.h"

class NodoBitacora {
private:
	EstadoBitacora* dato;
	NodoBitacora* sig;
public:
	// Constructor por defecto
	NodoBitacora();
	// Constructor con dato
	NodoBitacora(EstadoBitacora* d);
	// Destructor (no borra 'dato', ListaBitacora se encarga)
	~NodoBitacora();

	// Getters
	EstadoBitacora* getDato();
	NodoBitacora* getSig();

	// Setters
	void setDato(EstadoBitacora* d);
	void setSig(NodoBitacora* s);
};
