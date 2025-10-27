#include "ListaColaboradores1.h"
ListaColaboradores1::ListaColaboradores1() : ListaPersonas() {}
ListaColaboradores1::~ListaColaboradores1() {}
string ListaColaboradores1::mostrarPersonas(int ver) {
	stringstream ss;
	ss << "Lista de Colaboradores:\n";
	int cant = 1;
	NodoP* actual = primero;
	while (actual) {
		ss <<cant++<<". " << actual->getDato()->toString() << "\n";
		actual = actual->getSig();
	}
	if (ver == 0) {
		ss <<cant++<<". " << "Agregar Colaborador\n";
		ss << cant++ << ". " << "Eliminar Colaborador\n";
	}
	ss << cant++ << ". " << "Regresar\n";
	return ss.str();
}
