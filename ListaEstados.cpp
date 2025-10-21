#include "ListaEstados.h"
ListaEstados::ListaEstados() {
	primero = nullptr;
	ultimo = nullptr;
	tam = 0;
}
ListaEstados::~ListaEstados() {
	NodoEstadoCarro* actual = primero;
	while (actual != nullptr) {
		NodoEstadoCarro* siguiente = actual->getSig();
		delete actual;
		actual = siguiente;
	}
}
// Getters
NodoEstadoCarro* ListaEstados::getPrimero() {
	return primero;
}
NodoEstadoCarro* ListaEstados::getUltimo() {
	return ultimo;
}
int ListaEstados::getTam() {
	return tam;
}
bool ListaEstados::insertarInicio(string e) {
	NodoEstadoCarro* nuevo = new NodoEstadoCarro(e);
	if (primero == nullptr) {
		primero = nuevo;
		ultimo = nuevo;
	}
	else {
		nuevo->setSig(primero);
		primero = nuevo;
	}
	tam++;
	return true;
}
NodoEstadoCarro* ListaEstados::buscarEstado(string e) {
	NodoEstadoCarro* actual = primero;
	while (actual != nullptr) {
		if (actual->getEstado() == e) {
			return actual;
		}
		actual = actual->getSig();
	}
	return nullptr; // No encontrado
}
string ListaEstados::mostrarEstados() {
	stringstream ss;
	NodoEstadoCarro* actual = primero;

	ss << "Actual estado del carro: " << actual->getEstado()<<endl;
	actual = actual->getSig();
	ss << "Bitacora de estados (Del ultimo estado al primer estado):" << endl;
	while (actual != nullptr) {
		ss << "- " << actual->getEstado() << endl;
		actual = actual->getSig();
	}

	return ss.str();
}

 