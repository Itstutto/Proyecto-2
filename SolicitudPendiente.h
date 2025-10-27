#pragma once
#include "SolicitudAlquiler.h"

class SolicitudPendiente : public SolicitudAlquiler {
public:
	SolicitudPendiente();
	// Constructor copia
	SolicitudPendiente(const SolicitudAlquiler& otra);
	SolicitudPendiente(Persona* cliente, Persona* colaborador, Carro* Vehiculo, int dias,
		const int& inicio, const int& entrega, double precioDiario, double precioTotal);
	~SolicitudPendiente() override;
	string toString() const override;
};
