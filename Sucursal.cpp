#include "Sucursal.h"

Sucursal::Sucursal(int numero) : numeroSucursal(numero) {
	planteles = new ListaPlantel();
	clientes = new ListaClientes1();
	colaboradores = new ListaColaboradores1();
}

Sucursal::~Sucursal() {
	delete planteles;
	delete clientes;
	delete colaboradores;
}

int Sucursal::getNumeroSucursal() const { return numeroSucursal; }
void Sucursal::setNumeroSucursal(int numero) { numeroSucursal = numero; }

ListaPlantel* Sucursal::getPlanteles() { return planteles; }
ListaClientes1* Sucursal::getClientes() { return clientes; }
ListaColaboradores1* Sucursal::getColaboradores() { return colaboradores; }
