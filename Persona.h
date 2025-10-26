#pragma once
#include <string>
class ListaSolicitudesContratos;
using namespace std;
class Persona
{
protected:
	string nombre;
	string id;
	ListaSolicitudesContratos* historial;
public:
	Persona();
	Persona(string nombre, string id);
	virtual ~Persona();
	string getNombre() const;
	string getId() const;
	ListaSolicitudesContratos* getHistorial() const;
	void setNombre(string nombre);
	void setId(string id);
	virtual string toString() const = 0;
	virtual string infoMenu() const = 0;
	virtual string mostrarModificar() const = 0;

};

