#pragma once
#include "SolicitudAlquiler.h"

class SolicitudPendiente : public SolicitudAlquiler {
public:
	SolicitudPendiente(Persona* cliente, Persona* colaborador, Carro* Vehiculo, int dias,
		const int& inicio, const int& entrega, double precioDiario, double precioTotal);
	~SolicitudPendiente() override;
	string toString() const override;
};
