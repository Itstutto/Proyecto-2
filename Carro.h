#pragma once
#include <string>
#include <sstream>
#include "ListaBitacora.h"
using namespace std;

class Carro
{
private:
	//De cada automovil interesa su marca, modelo, placa, tipo de licencia requerida, categoria, precio y estado.
	string placa;
	string modelo;
	string marca;
	string ubicacion;
	string tipoLicencia; // A1, A2, B1, B2, C1, C2
	char categoria; // A, B, C, D
	double precioDiario;
	ListaBitacora* historialEstados; // Bitacora de cambios de estado
public:
	static double precioA;
	static double precioB;
	static double precioC;
	static double precioD;
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
	double getPrecioDiario();
	string getEstadoCarro(); // Devuelve el estado actual del carro como texto
	string getHistorialEstados(); // Devuelve el historial de estados del carro

	// Setters
	void setPlaca(string p);
	void setModelo(string m);
	void setMarca(string ma);
	void setUbicacion(string u);
	void setTipoLicencia(string t);
	void setCategoria(char c);
	void actualizarPrecioDiario(); // Actualiza el precio diario basado en la categoria
	int setEstadosCarro(int estado, string idColaborador); // retorna 1 ok, -1 invalido, -2 mismo estado
	string mostrarCarro();
	string mostrarEstadosCarro();


	string toString();
};

