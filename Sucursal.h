#pragma once
#include "ListaPlantel.h"
#include "ListaClientes.h"
#include "ListaColaboradores.h"

class Sucursal {
private:
	int numeroSucursal;
	ListaPlantel* planteles;
	ListaClientes* clientes;
	ListaColaboradores* colaboradores;
public:
	Sucursal(int numero);
	~Sucursal();

	int getNumeroSucursal() const;
	void setNumeroSucursal(int numero);

	ListaPlantel* getPlanteles();
	ListaClientes* getClientes();
	ListaColaboradores* getColaboradores();
};
