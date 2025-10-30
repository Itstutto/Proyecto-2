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
	Plantel* buscarPlantel(char id);
	bool modificarPrecioCategoria(char categoria);
	int getTam();
	// Métodos adicionales
	bool insertarFinal(Plantel* p);
	bool eliminarPlantel(char id);
	string mostrarPlanteles();

	string mostrarListaPlanteles(int ver);
};

