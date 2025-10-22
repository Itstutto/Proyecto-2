#include "Persona.h"
Persona::Persona()
{
	nombre = "";
	id = "";
}
Persona::Persona(string nombre, string id)
{
	this->nombre = nombre;
	this->id = id;
}
Persona::~Persona(){}
string Persona::getNombre() const { return nombre; }
string Persona::getId() const { return id; }
void Persona::setNombre(string nombre){	this->nombre = nombre;}
void Persona::setId(string id){this->id = id;}


