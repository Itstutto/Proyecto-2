#pragma once
#include "Sucursal.h"
#include "ListaSucursales.h"

class Menu {
private:
	ListaSucursales* sucursales;
	bool validarEntero(int& opcion);
	bool validarFlotante(double& opcion);
	void inicializarDatos();
public:
	Menu();
	~Menu();
	void iniciar();
	void menuPrincipal();
};
