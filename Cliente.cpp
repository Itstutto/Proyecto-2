#include "Cliente.h"

Cliente::Cliente() : Persona(), paisResidencia("") {}

Cliente::Cliente(string nombre, string id, string paisResidencia)
	: Persona(nombre, id), paisResidencia(paisResidencia) {}

Cliente::~Cliente() {}

string Cliente::getPaisResidencia() { return paisResidencia; }

void Cliente::setPaisResidencia(string pais) { this->paisResidencia = pais; }

string Cliente::toString() const {
	stringstream ss;
	ss << "Cliente - Nombre: " << getNombre()
	   << ", ID: " << getId()
	   << ", Pais de residencia: " << paisResidencia;
	return ss.str();
}
