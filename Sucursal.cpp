#include "Sucursal.h"

Sucursal::Sucursal(int numero) : numeroSucursal(numero) {
	planteles = new ListaPlantel();
	clientes = new ListaClientes();
	colaboradores = new ListaColaboradores();
}

Sucursal::~Sucursal() {
	delete planteles;
	delete clientes;
	delete colaboradores;
}

int Sucursal::getNumeroSucursal() const { return numeroSucursal; }
void Sucursal::setNumeroSucursal(int numero) { numeroSucursal = numero; }

ListaPlantel* Sucursal::getPlanteles() { return planteles; }
ListaClientes* Sucursal::getClientes() { return clientes; }
ListaColaboradores* Sucursal::getColaboradores() { return colaboradores; }
