#include "SolicitudPendiente.h"
#include <sstream>

SolicitudPendiente::SolicitudPendiente(const string& codigo, const string& cliente, const string& colaborador,
									 const string& sucursal, const string& placa, int dias,
									 const string& inicio, const string& entrega, double precioDiario, double precioTotal)
	: SolicitudAlquiler(codigo, cliente, colaborador, sucursal, placa, dias, inicio, entrega, precioDiario, precioTotal, 1) {}

SolicitudPendiente::~SolicitudPendiente() {}

string SolicitudPendiente::toString() const {
	stringstream ss;
	ss << "Solicitud - " << toResumen();
	return ss.str();
}
