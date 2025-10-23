#pragma once
#include <string>
#include <sstream>
#include "NodoSuc.h"
class ListaSucursales
{
private:
	NodoSuc* primero;
	NodoSuc* ultimo;
	int tam;
public:
	ListaSucursales();
	~ListaSucursales();
	NodoSuc* getPrimero();
	NodoSuc* getUltimo();
	int getTam();
	bool insertarFinal(Sucursal* s);
	bool eliminarSucursal(int numero);
	NodoSuc* buscarSucursal(int numero);
	string mostrarSucursales(int ver);
	Sucursal* obtenerSucursalPorIndice(int indice);
};

