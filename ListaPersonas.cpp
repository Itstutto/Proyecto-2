#include "ListaPersonas.h"
ListaPersonas::ListaPersonas()
{
	primero = nullptr;
	ultimo = nullptr;
	tam = 0;
}
ListaPersonas::~ListaPersonas()
{
	NodoP* actual = primero;
	while (actual != nullptr) {
		NodoP* siguiente = actual->getSiguiente();
		delete actual->getDato();
		delete actual;
		actual = siguiente;
	}
}
NodoP* ListaPersonas::getPrimero() { return primero; }
NodoP* ListaPersonas::getUltimo() { return ultimo; }
int ListaPersonas::getTam() { return tam; }
bool ListaPersonas::insertarFinal(Persona* p)
{
	NodoP* nuevo = new NodoP(p);
	if (!nuevo) return false;
	// Evitar repetidos
	if(buscarPersona(p->getId()) != nullptr) {
		delete nuevo;
		return false;
	}
	if (tam == 0) {
		primero = nuevo;
		ultimo = nuevo;
	} else {
		ultimo->setSiguiente(nuevo);
		ultimo = nuevo;
	}
	tam++;
	return true;
}

bool ListaPersonas::eliminarPersona(string id)
{
	if (tam == 0) return false;
	NodoP* actual = primero;
	NodoP* anterior = nullptr;
	while (actual != nullptr && actual->getDato()->getId() != id) {
		anterior = actual;
		actual = actual->getSiguiente();
	}
	if (actual == nullptr) return false; // No encontrado
	if (anterior == nullptr) { // Eliminar el primero
		primero = actual->getSiguiente();
		if (primero == nullptr) ultimo = nullptr; // Lista queda vacia
	} else {
		anterior->setSiguiente(actual->getSiguiente());
		if (actual == ultimo) ultimo = anterior; // Eliminar el ultimo
	}
	delete actual->getDato();
	delete actual;
	tam--;
	return true;
}
Persona* ListaPersonas::buscarPersona(string id)
{
	NodoP* actual = primero;
	while (actual != nullptr) {
		if (actual->getDato()->getId() == id) {
			return actual->getDato();
		}
		actual = actual->getSiguiente();
	}
	return nullptr; // No encontrado
}


