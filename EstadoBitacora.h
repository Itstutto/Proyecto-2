#pragma once
#include <string>
#include <sstream>
#include <ctime>
using namespace std;

class EstadoBitacora {
private:
	int estadoAnterior;
	int estadoActual;
	string fechaCambio; // DD/MM/YYYY
	string idColaborador;
public:
	EstadoBitacora(int anterior, int actual, const string& colaborador);
	~EstadoBitacora();
	int getEstadoAnterior() const;
	int getEstadoActual() const;
	string getFechaCambio() const;
	string getIdColaborador() const;
	string toString() const;
};
