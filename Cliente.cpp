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
	ss << "----------------------------------------------" << endl
		<< "Cliente - Nombre: " << getNombre() << endl
	    << ", ID: " << getId() << endl
	    << ", Pais de residencia: " << paisResidencia << endl
		<< "----------------------------------------------";
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
		<< "------------------------------------------------------------------" << endl;
	s << "1). Modificar Cliente" << endl
		<< "------------------------------------------------------------------" << endl
		<< "2). Informacion del Cliente" << endl
		<< "------------------------------------------------------------------" << endl
		<< "3). Historial de Transacciones (Completadas, Rechazadas y Anuladas)" << endl 
		<< "------------------------------------------------------------------" << endl
		<< "4). Ver Solicitudes Pendientes (Alquileres Pendientes)" << endl
		<< "------------------------------------------------------------------" << endl
		<< "5). Regresar" << endl
		<< "------------------------------------------------------------------" << endl;
		s << "Seleccione una opcion: ";
	return s.str();

}

string Cliente::mostrarModificar() const
{
	stringstream s;
	//muestra en un menu las opciones que se pueden modificar 
	s << "1). Nombre " << endl
		<< "---------------------" << endl
		<< "2). ID " << endl
		<< "---------------------" << endl
		<< "3). Pais de residencia " << endl
		<< "---------------------" << endl;
	return s.str();
}
