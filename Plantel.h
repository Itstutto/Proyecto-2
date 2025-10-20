#pragma once
#include "Carro.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Plantel // Matriz de veh�culos "Estacionamiento" 
{
private:
	char identificador; // A, B, C, D
	int filas;
	int columnas;
	Carro*** estacionamiento; // Matriz din�mica de punteros a Carro
public:

	Plantel();
	Plantel(char id, int f, int c);
	~Plantel();
	// Getters
	char getIdentificador();
	int getFilas();
	int getColumnas();
	string getEspacioEstacionamiento(int f, int c);
	Carro* getCarroxPos(int f, int c);
	int getCanTotal();
	int getCanDisponibles();
	
	// Setters
	void setIdentificador(char id);
	void setFilas(int f);
	void setColumnas(int c);
	// M�todos adicionales
	bool agregarCarro(Carro* carro, int pos);
	bool eliminarCarro(int f, int c);
	string mostrarEstacionamiento(int ver);
};

