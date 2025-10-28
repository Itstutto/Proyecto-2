#pragma once
#include "ListaPersonas.h"
class ListaClientes1 : public ListaPersonas
{
public:
	ListaClientes1();
	~ListaClientes1();
	void eliminarColaboradorHistorial(string id);
	string mostrarPersonas(int ver) override;
};

