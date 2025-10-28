#include "EstadoBitacora.h"

// Genera la fecha actual en formato DD/MM/YYYY usando localtime_s como en Colaborador
static string fechaAhora() {
	time_t actual = time(0);
	tm local{};
	localtime_s(&local, &actual);
	stringstream ss;
	// DD
	if (local.tm_mday < 10) ss << '0';
	ss << local.tm_mday << '/';
	// MM
	int mes = local.tm_mon + 1;
	if (mes < 10) ss << '0';
	ss << mes << '/';
	// YYYY
	ss << (local.tm_year + 1900);
	return ss.str();
}

EstadoBitacora::EstadoBitacora(int anterior, int actual, const string& colaborador)
	: estadoAnterior(anterior), estadoActual(actual), idColaborador(colaborador), fechaCambio(fechaAhora()) {}

EstadoBitacora::~EstadoBitacora() {}

int EstadoBitacora::getEstadoAnterior() const { return estadoAnterior; }
int EstadoBitacora::getEstadoActual() const { return estadoActual; }
string EstadoBitacora::getFechaCambio() const { return fechaCambio; }
string EstadoBitacora::getIdColaborador() const { return idColaborador; }

string EstadoBitacora::toString() const {
	stringstream ss;
	if (estadoAnterior == estadoActual) {
		ss << "Primer estado registrado: "<< estadoActual << "| Fecha: " << fechaCambio << " (ID colaborador: " << idColaborador << ")";
	}
	else {
		ss << fechaCambio << "| De: " << estadoAnterior << "| ->  |A:" << estadoActual << "| "
			<< " (ID colaborador: " << idColaborador << ")";
	}
	return ss.str();
}
