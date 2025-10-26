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

string Cliente::mostrarCliente() const
{
	stringstream s;
 	s << nombre<<endl
		<< "-----------------------------------------" << endl;
	s<<"1. Modificar Cliente"<<endl
		<< "2. Informacion del Cliente" << endl
		<< "3. Historial de Alquileres (funcionalidad no implementada)" << endl
		<< "4. Salir" << endl;
	return s.str();

}

string Cliente::mostrarModificar() const
{
	stringstream s;
	//muestra en un menu las opciones que se pueden modificar 
	s << "1. Nombre " << endl
		<< "2. ID " << endl
		<< "3. Pais de residencia " << endl;
	return s.str();
}
