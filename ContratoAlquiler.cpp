#include "ContratoAlquiler.h"
#include <sstream>

// IMPLEMENTACIÓN DEL CONSTRUCTOR: Inicializar el estado detallado a 'Aprobado Pendiente de Ejecución' (2)
ContratoAlquiler::ContratoAlquiler(const string& codigo, const string& cliente, const string& colaborador,
					 const string& sucursal, const string& placa, int dias,
					 const string& inicio, const string& entrega, double precioDiario, double precioTotal)
	// Llama al constructor base con estadoTransaccion = 2 (Aprobada/Contrato)
	: SolicitudAlquiler(codigo, cliente, colaborador, sucursal, placa, dias, inicio, entrega, precioDiario, precioTotal, 2),
	  estadoDetalladoContrato(2), // Por defecto: Aprobado Pendiente de Ejecución
	  detalleFinalizacion("")
{}

// IMPLEMENTACIÓN DE GETTERS Y SETTERS
int ContratoAlquiler::getEstadoDetallado() const {
	return estadoDetalladoContrato;
}

string ContratoAlquiler::getEstadoDetalladoStr() const {
	switch (estadoDetalladoContrato) {
		case 1: return "Aprobado en alquiler";
		case 2: return "Aprobado pendiente de ejecucion";
		case 3: return string("Finalizado (") + detalleFinalizacion + ")";
		default: return "ERROR";
	}
}

void ContratoAlquiler::setEstadoDetallado(int nuevoEstado, const string& detalle) {
	estadoDetalladoContrato = nuevoEstado;
	// La lógica de detalle solo aplica si el nuevo estado es 3 (Finalizado)
	if (nuevoEstado == 3) {
		detalleFinalizacion = detalle;
	} else {
		detalleFinalizacion = "";
	}
}

// ACTUALIZAR toString() para incluir el estado detallado
string ContratoAlquiler::toString() const {
	stringstream ss;
	ss << "Contrato - " << toResumen() << " | Estado Operativo: " << getEstadoDetalladoStr();
	// Aquí se pueden agregar más detalles del Contrato (fechas, precios, etc.)
	return ss.str();
}
