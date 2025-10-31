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
void ListaSucursales::alquilarCarro(Plantel* alquiler, string placa)
{
	// busca el carro en todos los planeteles de todas las sucursales, lo mueve del plantel donde esta al plantel de alquiler
	NodoSuc* actual = primero;
	while (actual != nullptr) {
		Carro* carro = actual->getDato()->buscarCarroPorPlaca(placa);
		if (carro) {
			// Encontrado el carro, moverlo al plantel de alquiler
			Plantel* origen = nullptr;
			NodoPl* nodoPlantel = actual->getDato()->getPlanteles()->getPrimero();
			while (nodoPlantel != nullptr) {
				if (nodoPlantel->getDato()->getCarroxPlaca(placa)) {
					origen = nodoPlantel->getDato();
					break;
				}
				nodoPlantel = nodoPlantel->getSig();
			}
			if (origen) {
				origen->moverCarro(placa, alquiler);
			}
			return; // Carro movido, salir de la función
		}
		actual = actual->getSig();
	}

}
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
	if (ver == 1 || ver == 0) {
		s << num++ << ".) Salir\n";
	}
	return s.str();

}
Sucursal* ListaSucursales::obtenerSucursalPorIndice(int indice)
{
	indice--; // Ajustar a 0-based
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

bool ListaSucursales::modificarPrecioCategoria(char categoria, double nuevoPrecio)
{
	if (!primero) return false;
	if (categoria < 'A' || categoria > 'D' || nuevoPrecio < 0) return false;
	switch (categoria) {
	case 'A':
		Carro::precioA = nuevoPrecio;
		break;
	case 'B':
		Carro::precioB = nuevoPrecio;
		break;
	case 'C':
		Carro::precioC = nuevoPrecio;
		break;
	case 'D':
		Carro::precioD = nuevoPrecio;
		break;
	default:
		return false;
	}
	NodoSuc* actual = primero;
	while (actual) {
		actual->getDato()->getPlanteles()->modificarPrecioCategoria(categoria); // solo categoria porque 
		actual = actual->getSig();
	}
	return true;
}

// Implementacion del Reporte Global (Reporte 1)
string ListaSucursales::generarReporteGlobalContratos() const {
	stringstream ss;
	ss << "\n======= REPORTE GLOBAL: CONTRATOS POR SUCURSAL (Mas Reciente a Antiguo) =======\n";

	NodoSuc* actual = primero;
	bool encontrado = false;

	while (actual) {
		ss << actual->getDato()->generarReporteContratosPorSucursal() << endl; // Llama al metodo de Sucursal
		encontrado = true;
		actual = actual->getSig();
	}

	if (!encontrado) {
		ss << "(No hay sucursales registradas en el sistema)." << endl;
	}

	ss << "=================================================================================\n";
	return ss.str();
}
