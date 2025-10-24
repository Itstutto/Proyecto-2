#pragma once
#include "ListaPersonas.h"
class ListaClientes1 : public ListaPersonas
{
public:
	ListaClientes1();
	~ListaClientes1();
	string mostrarPersonas(int ver) override;
};

