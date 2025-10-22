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
	string getNombre() const;
	string getId() const;
	void setNombre(string nombre);
	void setId(string id);
	virtual string toString() const = 0;

};

