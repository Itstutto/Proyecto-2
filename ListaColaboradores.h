#pragma once
#include <string>
#include <sstream>
#include "NodoCol.h"

using namespace std;

class ListaColaboradores {
private:
	NodoCol* primero;
	NodoCol* ultimo;
	int tam;
public:
	ListaColaboradores();
	~ListaColaboradores();

	NodoCol* getPrimero();
	NodoCol* getUltimo();
	int getTam();

	bool insertarFinal(Colaborador* co);
	bool eliminarColaborador(string id);
	Colaborador* buscarColaborador(string id);
	string mostrarColaboradores();
};
