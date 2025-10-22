#pragma once
#include "Persona.h"
#include <string>
#include <sstream>
#include <ctime>

using namespace std;

class Colaborador : public Persona
{
private:
	tm fechaContratacion; // fecha con estructura tm (c�digo existente)
	string fechaIngreso; // adicional, formato libre (DD/MM/AAAA)
public:
	Colaborador();
	Colaborador(string nombre, string id, int fechaContratacion); // 06102006 == 06/10/2006, 0 = actual
	Colaborador(string nombre, string id, string fechaIngreso);
	~Colaborador();

	string getFechaContratacion() const;
	void setFechaContratacion(int fecha);

	string getFechaIngreso();
	void setFechaIngreso(string fecha);
	string toString() const override;
};

