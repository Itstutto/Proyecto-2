#include "ListaPlantel.h"

ListaPlantel::ListaPlantel() {
	primero = nullptr;
	ultimo = nullptr;
	tam = 0;
}
ListaPlantel::~ListaPlantel() {
	NodoPl* actual = primero;
	while (actual != nullptr) {
		NodoPl* siguiente = actual->getSig();
		delete actual->getDato();
		delete actual;
		actual = siguiente;
	}
}
// Getters
NodoPl* ListaPlantel::getPrimero() {
	return primero;
}
NodoPl* ListaPlantel::getUltimo() {
	return ultimo;
}
NodoPl* ListaPlantel::buscarPlantel(int pos)
{
	pos--; // Ajustar para índice basado en 0
	if (pos < 0 || pos >= tam) return nullptr;
	NodoPl* actual = primero;
	for (int i = 0; i < pos; i++) {
		actual = actual->getSig();
	}
	return actual;
}
int ListaPlantel::getTam() {
	return tam;
}


bool ListaPlantel::insertarFinal(Plantel* p) {
	if (!p) return false;
	NodoPl* nuevo = new NodoPl(p);
	if (primero == nullptr) {
		primero = nuevo;
		ultimo = nuevo;
	} else {
		ultimo->setSig(nuevo);
		ultimo = nuevo;
	}
	tam++;
	return true;
}

bool ListaPlantel::eliminarPlantel(char id) {
	if (primero == nullptr) return false;
	NodoPl* actual = primero;
	NodoPl* anterior = nullptr;
	while (actual && actual->getDato()->getIdentificador() != id) {
		anterior = actual;
		actual = actual->getSig();
	}
	if (actual == nullptr) return false; // No encontrado
	if (anterior == nullptr) { // Eliminar el primero
		primero = actual->getSig();
		if (primero == nullptr) ultimo = nullptr; // Lista vacía
	} else {
		anterior->setSig(actual->getSig());
		if (actual == ultimo) ultimo = anterior; // Eliminar el último
	}
	delete actual->getDato();
	delete actual;
	tam--;
	return true;
}
Plantel* ListaPlantel::buscarPlantel(char id) {
	NodoPl* actual = primero;
	while (actual) {
		if (actual->getDato()->getIdentificador() == id) {
			return actual->getDato();
		}
		actual = actual->getSig();
	}
	return nullptr; // No encontrado
}

string ListaPlantel::mostrarPlanteles() {
	stringstream s;
	s << "Lista de Planteles:\n";
	NodoPl* actual = primero;
	while (actual) {
		s << "Plantel " << actual->getDato()->getIdentificador() << ": "
		  << actual->getDato()->getCanDisponibles() << " disponibles de "
		  << actual->getDato()->getCanTotal() << " totales.\n";
		actual = actual->getSig();
	}
	return s.str();
}

string ListaPlantel::mostrarListaPlanteles()
{
	stringstream ss;
	NodoPl* actual = primero;
	int numPlantel = 1;
	while (actual != nullptr) {
		ss << numPlantel<<". "<< "Plantel: "<< actual->getDato()->getIdentificador() << ") : \n";
		actual = actual->getSig();
		numPlantel++;
	}
	return ss.str();
}
