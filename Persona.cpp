#include "Persona.h"
#include "ListaSolicitudesContratos.h"
Persona::Persona()
{
	nombre = "";
	id = "";
	historial = new ListaSolicitudesContratos();
}
Persona::Persona(string nombre, string id)
{
	this->nombre = nombre;
	this->id = id;
	historial = new ListaSolicitudesContratos();
}
Persona::~Persona(){}
string Persona::getNombre() const { return nombre; }
string Persona::getId() const { return id; }
ListaSolicitudesContratos* Persona::getHistorial() const
{
	return historial;
}
void Persona::setNombre(string nombre){	this->nombre = nombre;}
void Persona::setId(string id){this->id = id;}


