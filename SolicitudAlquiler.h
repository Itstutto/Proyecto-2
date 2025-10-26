#pragma once
#include <string>
#include <sstream>
#include <ctime>
#include "Persona.h"
#include "Cliente.h"
#include "Colaborador.h"
#include "Carro.h"
using namespace std;




class SolicitudAlquiler {
protected:
	char tipoTransaccion; // 'S' para Solicitud, 'C' para Contrato
	int codigoTransaccion;
	Persona* cliente;
	Persona* colaborador;
	Carro* vehiculo;
	int diasAlquiler;
	tm fechaInicio;
	tm fechaEntrega;
	double precioDiario;
	double precioTotal;
	int estadoTransaccion; // 1=Pendiente, 2=Aprobada/Contrato, 3=Rechazada, 4=Anulada
public:
	SolicitudAlquiler();
	SolicitudAlquiler(Persona* cliente, Persona* colaborador, Carro* Vehiculo, int dias,
					 const int& inicio, const int& entrega, double precioDiario, double precioTotal,
					  char tipoTransaccion, int estado = 1);
	virtual ~SolicitudAlquiler();
	static int consecutivo;

	// Getters basicos
	string getCodigoTransaccion() const;
	int getEstadoTransaccion() const;
	void setEstadoTransaccion(int nuevoEstado); // NUEVO SETTER

	//setters y getters de todo
	Persona* getCliente() const;
	Persona* getColaborador() const;
	Carro* getCarro() const;
	tm getFechaInicioTM() const;
	tm getFechaEntregaTM() const;
	string getIdCliente() const;
	string getIdColaborador() const;
	string getPlacaVehiculo() const;
	int getDiasAlquiler() const;
	string getFechaInicio() const;
	string getFechaEntrega() const;
	double getPrecioDiario() const;
	double getPrecioTotal() const;

	void setCliente(Persona* p);
	void setColaborador(Colaborador* c);
	void setCarro(Carro* c);
	void setDiasAlquiler(int dias);
	void setFechaInicio(const int& inicio);
	void setFechaEntrega(const int& entrega);
	void setPrecioDiario(double precio);
	void setPrecioTotal(double precio);






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
