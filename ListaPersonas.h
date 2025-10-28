#pragma once
#include <string>
#include <sstream>
#include "NodoP.h"
using namespace std;
class ListaPersonas
{
protected:
	NodoP* primero;
	NodoP* ultimo;
	int tam;
public:
	ListaPersonas();
	~ListaPersonas();

	NodoP* getPrimero();
	NodoP* getUltimo();
	int getTam();

	void vehiculoEliminado(string placa);

	bool insertarFinal(Persona* p);
	bool eliminarPersona(string id);
	Persona* buscarPersona(string id);
	virtual string mostrarPersonas(int ver) = 0;
	Persona* obtenerPersonaPorIndice(int indice);
};

