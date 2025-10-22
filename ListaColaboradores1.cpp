#include "ListaColaboradores1.h"
ListaColaboradores1::ListaColaboradores1() : ListaPersonas() {}
ListaColaboradores1::~ListaColaboradores1() {}
string ListaColaboradores1::mostrarPersonas() {
	stringstream ss;
	NodoP* actual = getPrimero();
	while (actual != nullptr) {
		ss << "Colaborador - Nombre: " << actual->getDato()->getNombre()
		   << ", ID: " << actual->getDato()->getId() << "\n";
		actual = actual->getSiguiente();
	}
	return ss.str();
}
