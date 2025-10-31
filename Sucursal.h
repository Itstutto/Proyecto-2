#pragma once
#include "ListaPlantel.h"
#include "ListaColaboradores1.h"
#include "ListaClientes1.h"
#include "ListaSolicitudesContratos.h"

class Sucursal {
private:
	int numeroSucursal;
	ListaPlantel* planteles;
	ListaClientes1* clientes;
	ListaColaboradores1* colaboradores;
	ListaSolicitudesContratos* solicitudes;
	ListaSolicitudesContratos* contratos;

public:
	Sucursal();
	Sucursal(int numero);
	~Sucursal();

	int getNumeroSucursal() const;
	void setNumeroSucursal(int numero);

	ListaPlantel* getPlanteles();
	ListaClientes1* getClientes();
	ListaColaboradores1* getColaboradores();
	ListaSolicitudesContratos* getSolicitudes();
	ListaSolicitudesContratos* getContratos();

	Carro* buscarCarroPorPlaca(const string& placa);

	bool modificarPrecioCategoria(char categoria, double nuevoPrecio);


	// Lógica principal para convertir solicitud pendiente a contrato activo
	bool convertirSolicitudAContrato(int idSolicitud, const string& idColaboradorAprueba,
		ListaSolicitudesContratos* listaSolicitudes,
		ListaSolicitudesContratos* listaContratos,
		ListaClientes1* listaClientes,
		ListaColaboradores1* listaColaboradores);

	// REPORTE DE OCUPACIÓN DE PLANTELES (REPORTE 2)
	string generarReporteOcupacionPlanteles();

	// NUEVO: REPORTE DE CONTRATOS POR SUCURSAL
	string generarReporteContratosPorSucursal() const;

	string mostrarOpciones();
};
