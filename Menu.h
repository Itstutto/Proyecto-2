#pragma once
#include "Sucursal.h"

class Menu {
private:
	Sucursal* sucursalActual;
	void validarEntero(int& opcion);
	void submenuPersonas();
	void inicializarDatos();
public:
	Menu(Sucursal* s);
	void iniciar();
	void menuPrincipal();
};
