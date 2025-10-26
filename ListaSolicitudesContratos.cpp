#include "ListaSolicitudesContratos.h"

ListaSolicitudesContratos::ListaSolicitudesContratos() : primero(nullptr), ultimo(nullptr), tam(0) {}

ListaSolicitudesContratos::~ListaSolicitudesContratos() {
	NodoSolicitud* a = primero;
	while (a) {
		NodoSolicitud* s = a->getSig();
		delete a->getDato();
		delete a;
		a = s;
	}
}
int ListaSolicitudesContratos::getTam() const {
	return tam;
}

bool ListaSolicitudesContratos::insertarFinal(SolicitudAlquiler* s) {
	if (!s) return false;
	NodoSolicitud* n = new NodoSolicitud(s);
	if (!primero) {
		primero = ultimo = n;
	} else {
		ultimo->setSig(n);
		ultimo = n;
	}
	tam++;
	return true;
}

SolicitudAlquiler* ListaSolicitudesContratos::buscarTransaccion(const int& pos) {
	if (pos < 1 || pos > tam) return nullptr;
	NodoSolicitud* a = primero;
	int contador = 1;
	while (a) {
		if (contador == pos) {
			return a->getDato();
		}
		a = a->getSig();
		contador++;
	}
	return nullptr;
}

string ListaSolicitudesContratos::mostrarTransacciones() {
	stringstream ss;
	ss << "Transacciones:" << "\n";
	int num = 1;
	NodoSolicitud* a = primero;
	while (a) {
		ss << num<<") " << a->getDato()->toResumen() << "\n";
		a = a->getSig();
	}
	ss << ++num << ") Regresar\n";
	return ss.str();
}
string ListaSolicitudesContratos::toString() const {
	// muestra todas las transacciones en detalle
	stringstream ss;
	if (!primero) {
		ss << "No hay transacciones disponibles.\n";
		return ss.str();
	}
	NodoSolicitud* a = primero;
	while (a) {
		ss << a->getDato()->toString() << "\n";
		a = a->getSig();
	}
	return ss.str();
}
