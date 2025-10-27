#include "SolicitudPendiente.h"
#include <sstream>

SolicitudPendiente::SolicitudPendiente() : SolicitudAlquiler() {
}

SolicitudPendiente::SolicitudPendiente(const SolicitudAlquiler& otra) : SolicitudAlquiler(otra)
{
}

SolicitudPendiente::SolicitudPendiente(Persona* cliente, Persona* colaborador, Carro* Vehiculo, int dias,
	const int& inicio, const int& entrega, double precioDiario, double precioTotal)
	: SolicitudAlquiler(cliente, colaborador, Vehiculo, dias,
		inicio, entrega, precioDiario, precioTotal, 'S') {
}

SolicitudPendiente::~SolicitudPendiente() {}

string SolicitudPendiente::toString() const {
	stringstream ss;
	ss << "Solicitud - " << toResumen();
	return ss.str();
}
