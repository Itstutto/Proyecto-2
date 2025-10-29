#pragma once
#include <string>
#include <sstream>
#include "ClienteFisico.h"
#include "SolicitudAlquiler.h"
#include "NodoSolicitud.h"

class ListaSolicitudesContratos {
private:
	NodoSolicitud* primero;
	NodoSolicitud* ultimo;
	int tam;
public:
	ListaSolicitudesContratos();
	~ListaSolicitudesContratos();
	int getTam() const;
	bool insertarFinal(SolicitudAlquiler* s);
	SolicitudAlquiler* buscarTransaccion(const int& pos);
	SolicitudAlquiler* buscarTransaccionPorCodigo(const int& codigo); // Nuevo metodo
	bool transaccionesCliente(string id); // Verifica si un cliente tiene transacciones
	bool transaccionesColaborador(string id); // Verifica si un colaborador tiene transacciones
	void clienteEliminado(string id);
	void colaboradorEliminado(string id);
	void vehiculoEliminado(string placa);
	//Mostrar transacciones por colaborador, numeradas para seleccion
	// al selecionar una, devolver la transaccion
	void eliminarTransaccionPorCodigo(const int& codigo);
	string mostrarTransacciones();
	string toString() const;

	// NUEVOS METODOS
	string mostrarTransaccionesPorColaborador(string idColaborador);
	SolicitudAlquiler* obtenerTransaccionFiltradaPorIndice(string idColaborador, int indice);
};
