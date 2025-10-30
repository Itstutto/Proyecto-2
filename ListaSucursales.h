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
	void alquilarCarro(Plantel* alquiler, string placa); // mueve un carro al plantel de alquilados 
	bool insertarFinal(Sucursal* s);
	bool eliminarSucursal(int numero);
	NodoSuc* buscarSucursal(int numero);
	string mostrarSucursales(int ver);
	Sucursal* obtenerSucursalPorIndice(int indice);
	bool modificarPrecioCategoria(char categoria, double nuevoPrecio);
};

