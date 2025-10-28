#pragma once
#include "ListaPersonas.h"
class ListaColaboradores1 : public ListaPersonas
{
	public:
	ListaColaboradores1();
	void eliminarClienteHistorial(string id);
	~ListaColaboradores1();
	string mostrarPersonas(int ver) override;
};

