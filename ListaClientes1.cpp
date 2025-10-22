#include "ListaClientes1.h"
ListaClientes1::ListaClientes1() : ListaPersonas() {}
ListaClientes1::~ListaClientes1() {}
string ListaClientes1::mostrarPersonas() {
	stringstream ss;
	ss << "Lista de Clientes:\n";
	NodoP* actual = primero;
	while (actual) {
		ss << "- " << actual->getDato()->toString() << "\n";
		actual = actual->getSig();
	}
	return ss.str();
}
