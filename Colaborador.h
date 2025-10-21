#pragma once
#include "Persona.h"
#include <string>
#include <sstream>
#include <ctime>
class Colaborador : public Persona
{
private:
	tm fechaContratacion;
public:
	Colaborador();
	Colaborador(string nombre, string id, int fechaContratacion);
	~Colaborador();
	string getFechaContratacion();
	void setFechaContratacion(int fecha);
};

