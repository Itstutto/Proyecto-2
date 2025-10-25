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
	ListaSolicitudesContratos* transacciones;
public:
	Sucursal();
	Sucursal(int numero);
	~Sucursal();

	int getNumeroSucursal() const;
	void setNumeroSucursal(int numero);

	ListaPlantel* getPlanteles();
	ListaClientes1* getClientes();
	ListaColaboradores1* getColaboradores();
	ListaSolicitudesContratos* getTransacciones();


	string mostrarOpciones();
};
