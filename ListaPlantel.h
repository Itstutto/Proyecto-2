#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "NodoPl.h"
using namespace std;
class ListaPlantel
{
private:
	NodoPl* primero;
	NodoPl* ultimo;
	int tam;
public:
	ListaPlantel();
	~ListaPlantel();
	// Getters
	NodoPl* getPrimero();
	NodoPl* getUltimo();
	Plantel* buscarPlantel(int pos);
	int getTam();
	// M�todos adicionales
	bool insertarFinal(Plantel* p);
	bool eliminarPlantel(char id);
	Plantel* buscarPlantel(char id);
	string mostrarPlanteles();




	string mostrarListaPlanteles();
};

