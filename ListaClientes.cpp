#include "ListaClientes.h"

ListaClientes::ListaClientes() : primero(nullptr), ultimo(nullptr), tam(0) {}

ListaClientes::~ListaClientes() {
	NodoCl* actual = primero;
	while (actual) {
		NodoCl* sig = actual->getSig();
		delete actual->getDato();
		delete actual;
		actual = sig;
	}
}

NodoCl* ListaClientes::getPrimero() { return primero; }
NodoCl* ListaClientes::getUltimo() { return ultimo; }
int ListaClientes::getTam() { return tam; }

bool ListaClientes::insertarFinal(Cliente* c) {
	if (!c) return false;
	NodoCl* nuevo = new NodoCl(c);
	if (!primero) {
		primero = ultimo = nuevo;
	} else {
		ultimo->setSig(nuevo);
		ultimo = nuevo;
	}
	tam++;
	return true;
}

bool ListaClientes::eliminarCliente(string id) {
	if (!primero) return false;
	NodoCl* actual = primero;
	NodoCl* anterior = nullptr;
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

Cliente* ListaClientes::buscarCliente(string id) {
	NodoCl* actual = primero;
	while (actual) {
		if (actual->getDato()->getId() == id) return actual->getDato();
		actual = actual->getSig();
	}
	return nullptr;
}

string ListaClientes::mostrarClientes() {
	stringstream ss;
	ss << "Lista de Clientes:\n";
	NodoCl* actual = primero;
	while (actual) {
		ss << "- " << actual->getDato()->toString() << "\n";
		actual = actual->getSig();
	}
	return ss.str();
}
