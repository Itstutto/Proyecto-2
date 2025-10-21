#pragma once
#include <string>
using namespace std;
class Persona
{
private:
	string nombre;
	string id;
public:
	Persona();
	Persona(string nombre, string id);
	virtual ~Persona();
	string getNombre();
	string getId();
	void setNombre(string nombre);
	void setId(string id);

};

