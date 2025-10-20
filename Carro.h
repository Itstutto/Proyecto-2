#pragma once
#include <string>
#include <sstream>
#include "ListaEstados.h"
using namespace std;	

class Carro
{
private:
	//De cada automóvil interesa su marca, modelo, placa, tipo de licencia requerida, categoría, precio y estado.
	string placa;
	string modelo;
	string marca;
	string ubicacion;
	string tipoLicencia; // A1, A2, B1, B2, C1, C2
	char categoria; // A, B, C, D
	ListaEstados* estadosCarro; // Lista de estados del carro (Disponible, Alquilado, Revisión, Lavado)
public:
	Carro();
	Carro(string placa, string modelo, string marca, string ubicacion, string tipoLicencia, char categoria);
	~Carro();
	// Getters
	string getPlaca();
	string getModelo();
	string getMarca();
	string getUbicacion();
	string getTipoLicencia();
	char getCategoria();
	string getEstadoCarro(); // Devuelve el estado actual del carro
	string getHistorialEstados(); // Devuelve el historial de estados del carro

	// Setters
	void setPlaca(string p);
	void setModelo(string m);
	void setMarca(string ma);
	void setUbicacion(string u);
	void setTipoLicencia(string t);
	void setCategoria(char c);
	int setEstadosCarro(int estado); //entero para enviar correctamente los errores

	string toString();
};

