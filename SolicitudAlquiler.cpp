#include "SolicitudAlquiler.h"

SolicitudAlquiler::SolicitudAlquiler(const string& codigo, const string& cliente, const string& colaborador,
									 const string& sucursal, const string& placa, int dias,
									 const string& inicio, const string& entrega, double pDiario, double pTotal,
									 int estado)
	: codigoTransaccion(codigo), idCliente(cliente), idColaborador(colaborador), idSucursal(sucursal), placaVehiculo(placa),
	  diasAlquiler(dias), fechaInicio(inicio), fechaEntrega(entrega), precioDiario(pDiario), precioTotal(pTotal),
	  estadoTransaccion(estado) {}

SolicitudAlquiler::~SolicitudAlquiler() {}

string SolicitudAlquiler::getCodigoTransaccion() const { return codigoTransaccion; }
int  SolicitudAlquiler::getEstadoTransaccion() const { return estadoTransaccion; }

// IMPLEMENTACIÓN DEL SETTER PARA EL ESTADO GENERAL DE LA TRANSACCIÓN
void SolicitudAlquiler::setEstadoTransaccion(int nuevoEstado) {
	if (nuevoEstado >= 1 && nuevoEstado <= 4) {
		estadoTransaccion = nuevoEstado;
	}
}

string SolicitudAlquiler::toResumen() const {
	stringstream ss;
	ss << codigoTransaccion << " - " << placaVehiculo << " - Cliente: " << idCliente << " - Estado: " << estadoTransaccion;
	return ss.str();
}

NodoSolicitud::NodoSolicitud() : dato(nullptr), sig(nullptr) {}
NodoSolicitud::NodoSolicitud(SolicitudAlquiler* d) : dato(d), sig(nullptr) {}
NodoSolicitud::~NodoSolicitud() {}
SolicitudAlquiler* NodoSolicitud::getDato() { return dato; }
NodoSolicitud* NodoSolicitud::getSig() { return sig; }
void NodoSolicitud::setDato(SolicitudAlquiler* d) { dato = d; }
void NodoSolicitud::setSig(NodoSolicitud* s) { sig = s; }
