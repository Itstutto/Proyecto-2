#include "ListaBitacora.h"

ListaBitacora::ListaBitacora() : primero(nullptr), ultimo(nullptr), tam(0) {}

ListaBitacora::~ListaBitacora() {
	NodoBitacora* actual = primero;
	while (actual) {
		NodoBitacora* s = actual->getSig();
		delete actual->getDato();
		delete actual;
		actual = s;
	}
}

NodoBitacora* ListaBitacora::getPrimero() { return primero; }
NodoBitacora* ListaBitacora::getUltimo() { return ultimo; }
int ListaBitacora::getTam() { return tam; }

bool ListaBitacora::insertarFinal(EstadoBitacora* e) {
	if (!e) return false;
	NodoBitacora* n = new NodoBitacora(e);
	if (!primero) {
		primero = ultimo = n;
	} else {
		ultimo->setSig(n);
		ultimo = n;
	}
	tam++;
	return true;
}

EstadoBitacora* ListaBitacora::getUltimoEstado() {
	return ultimo ? ultimo->getDato() : nullptr;
}

string ListaBitacora::mostrarBitacora() {
	stringstream ss;
	ss << " Bitacora de estados:" << endl;
	ss << " Estados: 1=Disponible, 2=Alquilado, 3=Devuelto, 4=En Revision, 5=Lavado" << endl << endl;
	NodoBitacora* a = primero;
	while (a) {
		if (!a->getSig()) ss << " Estado actual: " << endl;
		ss << a->getDato()->toString() << endl;
		a = a->getSig();
	} 
	return ss.str();
}
