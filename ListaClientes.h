#pragma once
#include <string>
#include <sstream>
#include "NodoCl.h"

using namespace std;

class ListaClientes {
private:
	NodoCl* primero;
	NodoCl* ultimo;
	int tam;
public:
	ListaClientes();
	~ListaClientes();

	NodoCl* getPrimero();
	NodoCl* getUltimo();
	int getTam();

	bool insertarFinal(Cliente* c);
	bool eliminarCliente(string id);
	Cliente* buscarCliente(string id);
	string mostrarClientes();
};
