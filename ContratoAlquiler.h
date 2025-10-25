#pragma once
#include "SolicitudAlquiler.h"

class ContratoAlquiler : public SolicitudAlquiler {
public:
	ContratoAlquiler(const string& codigo, const string& cliente, const string& colaborador,
					 const string& sucursal, const string& placa, int dias,
					 const string& inicio, const string& entrega, double precioDiario, double precioTotal)
		: SolicitudAlquiler(codigo, cliente, colaborador, sucursal, placa, dias, inicio, entrega, precioDiario, precioTotal, 2) {}
	~ContratoAlquiler() override {}
	string toString() const override;
};
