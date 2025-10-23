#include "Sucursal.h"
Sucursal::Sucursal() : numeroSucursal(0) {
	planteles = new ListaPlantel();
	clientes = new ListaClientes1();
	colaboradores = new ListaColaboradores1();
}

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
//usar "endl" en vez de \n (aplica en todo)
string Sucursal::mostrarOpciones() {
	stringstream ss;
	ss << "-------------------------------------------------" << endl;
	ss << "Sucursal Numero: " << numeroSucursal << endl
		<< "1. Clientes" << endl
		<< "2. Colaboradores" << endl
		<< "3. Planteles" << endl
		<< "4. Contratos" << endl
		<< "5. Regresar al menu principal" << endl;
	ss << "-------------------------------------------------" << endl;
	return ss.str();
}


