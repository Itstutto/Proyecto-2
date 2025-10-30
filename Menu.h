#pragma once
#include "Sucursal.h"
#include "ListaSucursales.h"
#include "ListaSolicitudesContratos.h"
class Cliente; // forward declaration
class Menu {
private:
	ListaSucursales* sucursales;
	Plantel* alquilados; // Plantel temporal para carros alquilados
	bool validarEntero(int& opcion);
	bool validarFlotante(double& opcion);
	void inicializarDatos();
	// Función auxiliar que maneja el submenú de gestión de solicitudes de un colaborador específico
	void mostrarTransaccionesColaborador(Sucursal* s, Colaborador* colab); 
	// Función auxiliar para el submenú de solicitudes de un cliente específico (NUEVA)
	void mostrarTransaccionesCliente(Sucursal* s, Cliente* cli);
public:
	Menu();
	~Menu();

	void gestionarTransacciones(ListaSolicitudesContratos* lsc);


	void iniciar();
	void menuPrincipal();
};
