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
		NodoP* siguiente = actual->getSig();
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
		ultimo->setSig(nuevo);
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
		actual = actual->getSig();
	}
	if (actual == nullptr) return false; // No encontrado
	if (anterior == nullptr) { // Eliminar el primero
		primero = actual->getSig();
		if (primero == nullptr) ultimo = nullptr; // Lista queda vacia
	} else {
		anterior->setSig(actual->getSig());
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
		actual = actual->getSig();
	}
	return nullptr; // No encontrado
}

Persona* ListaPersonas::obtenerPersonaPorIndice(int indice)
{
	indice--; // Ajustar a 0-based
	if (indice < 0 || indice >= tam) return nullptr;
	NodoP* actual = primero;
	for (int i = 0; i < indice; i++) {
		actual = actual->getSig();
	}
	return actual->getDato();
}


