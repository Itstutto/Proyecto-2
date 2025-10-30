#include "Cliente.h"
#include "ListaSolicitudesContratos.h"

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


string Cliente::mostrarSolicitudesPendientesRealizadas(ListaSolicitudesContratos* lsc) {
	if (!lsc) return "Error: Lista de solicitudes no proporcionada.";
	// Delega la tarea de filtrado y visualización a la clase lista.
	return lsc->mostrarTransaccionesPorCliente(getId()); 
}

// Modificación de mostrarCliente() para incluir la nueva opción 4
string Cliente::mostrarCliente() const
{
	stringstream s;
 	s << nombre<<endl
		<< "-----------------------------------------" << endl;
	s<<"1. Modificar Cliente"<<endl
		<< "2. Informacion del Cliente" << endl
		<< "3. Historial de Transacciones (Completadas, Rechazadas y Anuladas)" << endl // Nombre actualizado y funcional
        << "4. Ver Solicitudes Pendientes (Alquileres Pendientes)" << endl
		<< "5. Regresar" << endl;
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
