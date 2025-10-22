#pragma once
#include "Persona.h"
#include <string>
#include <sstream>

using namespace std;

class Cliente : public Persona {
private:
	string paisResidencia;
public:
	Cliente();
	Cliente(string nombre, string id, string paisResidencia);
	virtual ~Cliente();

	string getPaisResidencia();
	void setPaisResidencia(string pais);

	virtual string toString() const; // virtual para ser sobrescrito
};
