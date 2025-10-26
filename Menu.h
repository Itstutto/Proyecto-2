#pragma once
#include "Sucursal.h"
#include "ListaSucursales.h"
#include "ListaSolicitudesContratos.h"
class Menu {
private:
	ListaSucursales* sucursales;
	bool validarEntero(int& opcion);
	bool validarFlotante(double& opcion);
	void inicializarDatos();
public:
	Menu();
	~Menu();

	void gestionarTransacciones(ListaSolicitudesContratos* lsc);


	void iniciar();
	void menuPrincipal();
};
