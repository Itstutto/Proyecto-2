#include "ListaColaboradores.h"

ListaColaboradores::ListaColaboradores() : primero(nullptr), ultimo(nullptr), tam(0) {}

ListaColaboradores::~ListaColaboradores() {
	NodoCol* actual = primero;
	while (actual) {
		NodoCol* sig = actual->getSig();
		delete actual->getDato();
		delete actual;
		actual = sig;
	}
}

NodoCol* ListaColaboradores::getPrimero() { return primero; }
NodoCol* ListaColaboradores::getUltimo() { return ultimo; }
int ListaColaboradores::getTam() { return tam; }

bool ListaColaboradores::insertarFinal(Colaborador* co) {
	if (!co) return false;
	NodoCol* nuevo = new NodoCol(co);

	if (buscarColaborador(co->getId())) return false; // Evitar duplicados

	if (!primero) {
		primero = ultimo = nuevo;
	} else {
		ultimo->setSig(nuevo);
		ultimo = nuevo;
	}
	tam++;
	return true;
}

bool ListaColaboradores::eliminarColaborador(string id) {
	if (!primero) return false;
	NodoCol* actual = primero;
	NodoCol* anterior = nullptr;
	while (actual && actual->getDato()->getId() != id) {
		anterior = actual;
		actual = actual->getSig();
	}
	if (!actual) return false;
	if (!anterior) {
		primero = actual->getSig();
		if (!primero) ultimo = nullptr;
	} else {
		anterior->setSig(actual->getSig());
		if (actual == ultimo) ultimo = anterior;
	}
	delete actual->getDato();
	delete actual;
	tam--;
	return true;
}

Colaborador* ListaColaboradores::buscarColaborador(string id) {
	if (!primero) return nullptr;
	NodoCol* actual = primero;
	while (actual) {
		if (actual->getDato()->getId() == id) return actual->getDato();
		actual = actual->getSig();
	}
	return nullptr;
}

string ListaColaboradores::mostrarColaboradores() {
	stringstream ss;
	ss << "Lista de Colaboradores:\n";
	NodoCol* actual = primero;
	while (actual) {
		ss << "- " << actual->getDato()->toString() << "\n";
		actual = actual->getSig();
	}
	return ss.str();
}
