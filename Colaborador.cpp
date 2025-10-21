#include "Colaborador.h"
Colaborador::Colaborador() : Persona()
{
	time_t actual = time(0);
	localtime_s(&this->fechaContratacion, &actual);
}
Colaborador::Colaborador(string nombre, string id, int fechaContratacion) : Persona(nombre, id)
{
	//Si el usuario digita "0" usa la fecha actual, si no , usa la fecha digitada (06102006 == 06/10/2006) 
	// se divide la fecha primero
	if (fechaContratacion == 0) {
		time_t actual = time(0);
		localtime_s(&this->fechaContratacion, &actual);
	}
	else {
		this->fechaContratacion.tm_year = (fechaContratacion % 10000) - 1900;
		this->fechaContratacion.tm_mon = ((fechaContratacion / 10000) % 100) - 1;
		this->fechaContratacion.tm_mday = (fechaContratacion / 1000000);
	}
}
Colaborador::~Colaborador()
{
}
string Colaborador::getFechaContratacion()
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

