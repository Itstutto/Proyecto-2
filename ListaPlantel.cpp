#include "ListaPlantel.h"

ListaPlantel::ListaPlantel() {
	primero = nullptr;
	ultimo = nullptr;
	tam = 0;
}
ListaPlantel::~ListaPlantel() {
	NodoPl* actual = primero;
	while (actual != nullptr) {
		NodoPl* siguiente = actual->sig;
		delete actual->dato;
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
		actual = actual->sig;
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
		ultimo->sig = nuevo;
		ultimo = nuevo;
	}
	tam++;
	return true;
}

bool ListaPlantel::eliminarPlantel(char id) {
	if (primero == nullptr) return false;
	NodoPl* actual = primero;
	NodoPl* anterior = nullptr;
	while (actual && actual->dato->getIdentificador() != id) {
		anterior = actual;
		actual = actual->sig;
	}
	if (actual == nullptr) return false; // No encontrado
	if (anterior == nullptr) { // Eliminar el primero
		primero = actual->sig;
		if (primero == nullptr) ultimo = nullptr; // Lista vacía
	} else {
		anterior->sig = actual->sig;
		if (actual == ultimo) ultimo = anterior; // Eliminar el último
	}
	delete actual->dato;
	delete actual;
	tam--;
	return true;
}
Plantel* ListaPlantel::buscarPlantel(char id) {
	NodoPl* actual = primero;
	while (actual) {
		if (actual->dato->getIdentificador() == id) {
			return actual->dato;
		}
		actual = actual->sig;
	}
	return nullptr; // No encontrado
}

string ListaPlantel::mostrarPlanteles() {
	stringstream s;
	s << "Lista de Planteles:\n";
	NodoPl* actual = primero;
	while (actual) {
		s << "Plantel " << actual->dato->getIdentificador() << ": "
		  << actual->dato->getCanDisponibles() << " disponibles de "
		  << actual->dato->getCanTotal() << " totales.\n";
		actual = actual->sig;
	}
	return s.str();
}

string ListaPlantel::mostrarListaPlanteles()
{
	stringstream ss;
	NodoPl* actual = primero;
	int numPlantel = 1;
	while (actual != nullptr) {
		ss << numPlantel<<". "<< "Plantel: "<< actual->dato->getIdentificador() << ") : \n";
		actual = actual->sig;
		numPlantel++;
	}
	return ss.str();
}
