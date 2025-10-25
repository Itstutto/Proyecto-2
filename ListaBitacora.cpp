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
	ss << "Bitacora de estados:" << endl;
	NodoBitacora* a = primero;
	while (a) {
		ss << "- " << a->getDato()->toString() << endl;
		a = a->getSig();
	}
	return ss.str();
}
