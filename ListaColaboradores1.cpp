#include "ListaColaboradores1.h"
ListaColaboradores1::ListaColaboradores1() : ListaPersonas() {}
ListaColaboradores1::~ListaColaboradores1() {}
string ListaColaboradores1::mostrarPersonas() {
	stringstream ss;
	ss << "Lista de Colaboradores:\n";
	NodoP* actual = primero;
	while (actual) {
		ss << "- " << actual->getDato()->toString() << "\n";
		actual = actual->getSig();
	}
	return ss.str();
}
