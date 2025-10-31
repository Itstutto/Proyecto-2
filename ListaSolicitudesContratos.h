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

	
	string mostrarTransaccionesPorColaborador(string idColaborador);
	SolicitudAlquiler* obtenerTransaccionFiltradaPorIndice(string idColaborador, int indice);

	
	// Muestra las transacciones pendientes asociadas a un cliente específico, numeradas.
	string mostrarTransaccionesPorCliente(string idCliente);
	
	// Obtiene una transacción específica de la lista, basándose en el índice numerado del listado FILTRADO por cliente.
	SolicitudAlquiler* obtenerTransaccionFiltradaPorIndiceCliente(string idCliente, int indice);
	string mostrarHistorialCompletado() const;

	// NUEVOS METODOS (Para Reporte de Clientes - Rúbrica)
	// Devuelve un string con los códigos de contrato (estado 2) y el conteo por referencia.
	string obtenerReporteContratosCliente(string idCliente, int& contratosCount) const;
	
	// --- NUEVO MÉTODO PARA REPORTE POR VEHÍCULO ESPECÍFICO ---
	string generarReporteContratosPorVehiculo(string placaVehiculo) const;
};
