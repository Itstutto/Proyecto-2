#include "ListaSucursales.h"
ListaSucursales::ListaSucursales()
{
	primero = nullptr;
	ultimo = nullptr;
	tam = 0;
}
ListaSucursales::~ListaSucursales()
{
	NodoSuc* actual = primero;
	while (actual != nullptr) {
		NodoSuc* siguiente = actual->getSig();
		delete actual->getDato();
		delete actual;
		actual = siguiente;
	}
}
NodoSuc* ListaSucursales::getPrimero() { return primero; }
NodoSuc* ListaSucursales::getUltimo() { return ultimo; }
int ListaSucursales::getTam() { return tam; }
bool ListaSucursales::insertarFinal(Sucursal* s)
{
	NodoSuc* nuevo = new NodoSuc(s);
	if (!nuevo) return false;
	// Evitar repetidos
	if(buscarSucursal(s->getNumeroSucursal())) {
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
bool ListaSucursales::eliminarSucursal(int numero)
{
	if (tam == 0) return false;
	NodoSuc* actual = primero;
	NodoSuc* anterior = nullptr;
	while (actual != nullptr && actual->getDato()->getNumeroSucursal() != numero) {
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
NodoSuc* ListaSucursales::buscarSucursal(int numero)
{
	NodoSuc* actual = primero;
	while (actual != nullptr) {
		if (actual->getDato()->getNumeroSucursal() == numero) {
			return actual;
		}
		actual = actual->getSig();
	}
	return nullptr; // No encontrado
}
string ListaSucursales::mostrarSucursales(int ver)
{
	stringstream s;
	int num = 1;
	NodoSuc* actual = primero;
	while (actual != nullptr) {
		s << num << ".) Sucursal Numero: " << actual->getDato()->getNumeroSucursal() << "\n";
		actual = actual->getSig();
		num++;
	}
	if (ver == 0) {
		//opciones para, crear sucursal, eliminar sucursal, salir
		s << num++ << ".) Crear Sucursal\n";
		s << num++ << ".) Eliminar Sucursal\n";
	}
	s << num++ << ".) Salir\n";
	return s.str();

}
Sucursal* ListaSucursales::obtenerSucursalPorIndice(int indice)
{
	if (indice < 0 || indice >= tam) return nullptr;
	NodoSuc* actual = primero;
	int contador = 0;
	while (actual != nullptr) {
		if (contador == indice) {
			return actual->getDato();
		}
		actual = actual->getSig();
		contador++;
	}
	return nullptr; // No encontrado
}
