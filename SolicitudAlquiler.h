#pragma once
#include <string>
#include <sstream>

using namespace std;

class SolicitudAlquiler {
private:
	string codigoTransaccion;
	string idCliente;
	string idColaborador;
	string idSucursal;
	string placaVehiculo;
	int diasAlquiler;
	string fechaInicio;
	string fechaEntrega;
	double precioDiario;
	double precioTotal;
	int estadoTransaccion; // 1=Pendiente, 2=Aprobada/Contrato, 3=Rechazada, 4=Anulada
public:
	SolicitudAlquiler(const string& codigo, const string& cliente, const string& colaborador,
					 const string& sucursal, const string& placa, int dias,
					 const string& inicio, const string& entrega, double precioDiario, double precioTotal,
					 int estado = 1);
	virtual ~SolicitudAlquiler();

	// Getters basicos
	string getCodigoTransaccion() const;
	int getEstadoTransaccion() const;
	void setEstadoTransaccion(int nuevoEstado); // NUEVO SETTER
	string toResumen() const;

	virtual string toString() const = 0;
};

class NodoSolicitud {
private:
	SolicitudAlquiler* dato;
	NodoSolicitud* sig;
public:
	NodoSolicitud();
	NodoSolicitud(SolicitudAlquiler* d);
	~NodoSolicitud();
	SolicitudAlquiler* getDato();
	NodoSolicitud* getSig();
	void setDato(SolicitudAlquiler* d);
	void setSig(NodoSolicitud* s);
};
