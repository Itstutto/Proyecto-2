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
	// Función auxiliar que maneja el submenú de gestión de solicitudes de un colaborador específico
	void mostrarTransaccionesColaborador(Sucursal* s, Colaborador* colab); 
public:
	Menu();
	~Menu();

	void gestionarTransacciones(ListaSolicitudesContratos* lsc);


	void iniciar();
	void menuPrincipal();
};
