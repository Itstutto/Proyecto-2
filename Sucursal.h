#pragma once
#include "ListaPlantel.h"
#include "ListaColaboradores1.h"
#include "ListaClientes1.h"

class Sucursal {
private:
	int numeroSucursal;
	ListaPlantel* planteles;
	ListaClientes1* clientes;
	ListaColaboradores1* colaboradores;
public:
	Sucursal();
	Sucursal(int numero);
	~Sucursal();

	int getNumeroSucursal() const;
	void setNumeroSucursal(int numero);

	ListaPlantel* getPlanteles();
	ListaClientes1* getClientes();
	ListaColaboradores1* getColaboradores();


	string mostrarOpciones();
};
