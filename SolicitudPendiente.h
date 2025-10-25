#pragma once
#include "SolicitudAlquiler.h"

class SolicitudPendiente : public SolicitudAlquiler {
public:
	SolicitudPendiente(const string& codigo, const string& cliente, const string& colaborador,
					 const string& sucursal, const string& placa, int dias,
					 const string& inicio, const string& entrega, double precioDiario, double precioTotal);
	~SolicitudPendiente() override;
	string toString() const override;
};
