#include "ContratoAlquiler.h"
#include <sstream>

// IMPLEMENTACIÓN DEL CONSTRUCTOR: Inicializar el estado detallado a 'Aprobado Pendiente de Ejecución' (2)



ContratoAlquiler::ContratoAlquiler(const SolicitudAlquiler & solicitudAprobada)
{
	// Copia los atributos base desde la solicitud aprobada
	cliente = solicitudAprobada.getCliente();
	colaborador = solicitudAprobada.getColaborador();
	vehiculo = solicitudAprobada.getCarro();
	diasAlquiler = solicitudAprobada.getDiasAlquiler();
	fechaInicio = solicitudAprobada.getFechaInicioTM();
	fechaEntrega = solicitudAprobada.getFechaEntregaTM();
	precioDiario = solicitudAprobada.getPrecioDiario();
	precioTotal = solicitudAprobada.getPrecioTotal();
	estadoTransaccion = 2; // Cambia el estado de transacción a 'Aprobada/Contrato'
	tipoTransaccion = 'C'; // Indica que es un Contrato
	// Inicializa el estado detallado del contrato
	estadoDetalladoContrato = 2; // Aprobado pendiente de ejecucion
	detalleFinalizacion = "";

}

ContratoAlquiler::~ContratoAlquiler()
{
	cliente = nullptr;
	colaborador = nullptr;
	vehiculo = nullptr;
	// No se eliminan los punteros ya que no son dueños de la memoria
}



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
