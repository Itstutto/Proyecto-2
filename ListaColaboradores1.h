#pragma once
#include "ListaPersonas.h"
class ListaColaboradores1 : public ListaPersonas
{
	public:
	ListaColaboradores1();
	~ListaColaboradores1();
	string mostrarPersonas() override;
};

