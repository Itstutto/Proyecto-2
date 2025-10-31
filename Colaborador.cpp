#include "Colaborador.h"
#include <sstream>
#include "ListaSolicitudesContratos.h"

Colaborador::Colaborador() : Persona()
{
	time_t actual = time(0);
	localtime_s(&this->fechaContratacion, &actual);
	fechaIngreso = "";
}

Colaborador::Colaborador(string nombre, string id, int fechaContratacion)
	: Persona(nombre, id)
{
	if (fechaContratacion == 0) {
		time_t actual = time(0);
		localtime_s(&this->fechaContratacion, &actual);
	}
	else {
		this->fechaContratacion.tm_year = (fechaContratacion % 10000) - 1900;
		this->fechaContratacion.tm_mon = ((fechaContratacion / 10000) % 100) - 1;
		this->fechaContratacion.tm_mday = (fechaContratacion / 1000000);
		mktime(&this->fechaContratacion);
	}
	fechaIngreso = "";
}

Colaborador::Colaborador(string nombre, string id, string fechaIngreso)
	: Persona(nombre, id), fechaIngreso(fechaIngreso)
{
	time_t actual = time(0);
	localtime_s(&this->fechaContratacion, &actual);
}

Colaborador::~Colaborador() {}

string Colaborador::getFechaContratacion() const
{
	stringstream fecha;
	fecha << (this->fechaContratacion.tm_mday < 10 ? "0" : "") << this->fechaContratacion.tm_mday << "/";
	fecha << ((this->fechaContratacion.tm_mon + 1) < 10 ? "0" : "") << (this->fechaContratacion.tm_mon + 1) << "/";
	fecha << (this->fechaContratacion.tm_year + 1900);
	return fecha.str();
}

void Colaborador::setFechaContratacion(int fecha)
{
	//Si el usuario digita "0" usa la fecha actual, si no , usa la fecha digitada (06102006 == 06/10/2006) 
	// se divide la fecha primero
	if (fecha == 0) {
		time_t actual = time(0);
		localtime_s(&this->fechaContratacion, &actual);
	}
	else {
		this->fechaContratacion.tm_year = (fecha % 10000) - 1900;
		this->fechaContratacion.tm_mon = ((fecha / 10000) % 100) - 1;
		this->fechaContratacion.tm_mday = (fecha / 1000000);
		mktime(&this->fechaContratacion); // normalizar la estructura tm
	}
}

string Colaborador::getFechaIngreso() { return fechaIngreso; }

void Colaborador::setFechaIngreso(int fecha) {
	//setea ambos, fechaIngreso (string) y fechaContratacion (tm)
	// entero en formato DDMMYYYY
	int dia = fecha / 1000000;
	int mes = (fecha / 10000) % 100;
	int anio = fecha % 10000;
	fechaContratacion.tm_mday = dia;
	fechaContratacion.tm_mon = mes - 1; // tm_mon es 0-11
	fechaContratacion.tm_year = anio - 1900; // tm_year es años desde 1900
	stringstream ss;
	ss << (dia < 10 ? "0" : "") << dia << "/"
	   << (mes < 10 ? "0" : "") << mes << "/"
		<< anio;
	fechaIngreso = ss.str();
}

string Colaborador::toString() const {
	stringstream ss;
	ss << "Colaborador - Nombre: " << getNombre()
	   << ", ID: " << getId()
	   << ", Fecha de contratacion: " << getFechaContratacion()
	   << ", Fecha de ingreso: " << fechaIngreso;
	return ss.str();
}
string Colaborador::infoMenu() const {
	stringstream s;
	//muestra solo el nombre y el id, para el menu
	s << "Colaborador - Nombre: " << getNombre() << ", ID: " << getId();
	return s.str();
}

string Colaborador::mostrarModificar() const
{
	stringstream s;
	//muestra en un menu las opciones que se pueden modificar 
	s << "1. Nombre: " << nombre << endl
		<< "2. ID: " << id << endl
		<< "3. Fecha de contratacion: " << getFechaContratacion() << endl
		<< "4. Fecha de ingreso: " << fechaIngreso << endl
		<< "5. Salir" << endl;
	return s.str();
}


string Colaborador::mostrarSolicitudesPendientesGestionadas(ListaSolicitudesContratos* lsc) {
	if (!lsc) return "Error: Lista de solicitudes no proporcionada.";
	// Delega la tarea de filtrado y visualización a la clase lista.
	return lsc->mostrarTransaccionesPorColaborador(getId()); 
}

// Implementacion del Reporte 2: Contratos realizados por el colaborador
string Colaborador::generarReporteContratosRealizados() const {
	stringstream ss;
	ListaSolicitudesContratos* historial = getHistorial();

	ss << "\n--- REPORTE DE ALQUILERES POR COLABORADOR ESPECIFICO ---\n";
	ss << "ID Colaborador: " << getId() << ", Nombre: " << getNombre() << endl;
	ss << "----------------------------------------------------------" << endl;
	ss << "| Codigo Contrato | Placa Vehiculo | ID Cliente |" << endl;
	ss << "----------------------------------------------------------" << endl;

	NodoSolicitud* actual = historial->getPrimero();
	bool encontrado = false;

	while (actual) {
		SolicitudAlquiler* sol = actual->getDato();
		// Filtrar por Contratos (Estado 2 = Activo)
		if (sol->getEstadoTransaccion() == 2) {
			// Formato manual con espaciado
			ss << "| " << sol->getCodigoTransaccion() << "           ";
			ss << "| " << sol->getPlacaVehiculo() << "       ";
			ss << "| " << sol->getIdCliente() << "   |" << endl;
			encontrado = true;
		}
		actual = actual->getSig();
	}

	if (!encontrado) {
		ss << "(No se encontraron contratos activos realizados por este colaborador)." << endl;
	}
	ss << "----------------------------------------------------------" << endl;

	return ss.str();
}