#include "Menu.h"
#include <iostream>
#include "Plantel.h"
#include "Carro.h"
#include "ClienteFisico.h"
#include "ClienteJuridico.h"
#include "Colaborador.h"
#include "ListaClientes.h"
#include "ListaColaboradores.h"
#include "ListaPlantel.h"

using namespace std;

Menu::Menu(Sucursal* s) : sucursalActual(s) {}

void Menu::validarEntero(int& opcion) {
	if (cin.fail()) {
		cin.clear();
		cin.ignore(10000, '\n');
		opcion = 0;
	}
}

void Menu::inicializarDatos() {
	// Plantel y carros
	Plantel* plantel = new Plantel('A', 7, 8);

	Carro* carro1 = new Carro("123-ABC", "Corolla", "Toyota", "Madrid", "B1", 'B');
	Carro* carro2 = new Carro("567-DEF", "Civic", "Honda", "Barcelona", "B1", 'B');
	Carro* carro3 = new Carro("901-GHI", "Model S", "Tesla", "Valencia", "B2", 'A');
	Carro* carro4 = new Carro("345-JKL", "F-150", "Ford", "Sevilla", "C1", 'C');
	Carro* carro5 = new Carro("789-MNO", "Tucson", "Hyundai", "Bilbao", "B2", 'B');
	Carro* carro6 = new Carro("234-PQR", "Golf", "Volkswagen", "Granada", "B1", 'B');

	plantel->agregarCarro(carro1, 0);
	plantel->agregarCarro(carro2, 12);
	plantel->agregarCarro(carro3, 24);
	plantel->agregarCarro(carro4, 31);
	plantel->agregarCarro(carro5, 43);
	plantel->agregarCarro(carro6, 55);

	sucursalActual->getPlanteles()->insertarFinal(plantel);

	// Bucle de ejemplo para cambiar estado de carro1
	/*
	int estado = 0;
	do {
		cout << "Seleccione el estado del carro (estado actual: " << carro1->getEstadoCarro() << "):\n";
		cout << "1. Disponible\n";
		cout << "2. Alquilado\n";
		cout << "3. Devuelto\n";
		cout << "4. Revision\n";
		cout << "5. Lavado\n";
		cout << "Ingrese el numero correspondiente al estado: ";
		cin >> estado;
		validarEntero(estado);
		if (estado >= 1 && estado <= 5) {
			int comp = carro1->setEstadosCarro(estado);
			if (comp == 1) cout << "Estado cambiado correctamente\n";
			else if (comp == -1) cout << "No se puede cambiar al estado seleccionado desde el estado actual.\n";
			else if (comp == -2) cout << "El carro ya esta en el estado seleccionado.\n";
			else cout << "Opcion invalida.\n";
		}
	} while (estado != 6);
	*/
	// Clientes
	ClienteFisico* cf1 = new ClienteFisico("Juan Perez", "111", "Costa Rica");
	ClienteJuridico* cj1 = new ClienteJuridico("TechSolutions S.A.", "222", "Panama", "Software", 10.5);
	ClienteFisico* cf2 = new ClienteFisico("Ana Gomez", "333", "Nicaragua");
	ClienteJuridico* cj2 = new ClienteJuridico("Logistics Inc.", "444", "Costa Rica", "Transporte", 5.0);

	sucursalActual->getClientes()->insertarFinal(cf1);
	sucursalActual->getClientes()->insertarFinal(cj1);
	sucursalActual->getClientes()->insertarFinal(cf2);
	sucursalActual->getClientes()->insertarFinal(cj2);

	// Colaboradores
	Colaborador* co1 = new Colaborador("Maria Lopez", "C1", string("01/01/2024"));
	Colaborador* co1_dup = new Colaborador("Maria Lopez", "C1", string("01/01/2024"));
	Colaborador* co2 = new Colaborador("Carlos Soto", "C2", string("15/05/2023"));

	Persona* co1 = new Colaborador("Maria Lopez", "C1", string("01/01/2024"));
	Persona* co1_dup = new Colaborador("Maria Lopez", "C1", string("01/01/2024"));
	Persona* co2 = new Colaborador("Carlos Soto", "C2", string("15/05/2023"));

	sucursalActual->getColaboradores()->insertarFinal(co1);
	sucursalActual->getColaboradores()->insertarFinal(co1_dup);
	sucursalActual->getColaboradores()->insertarFinal(co2);
}

void Menu::iniciar() {
	inicializarDatos();
	menuPrincipal();
}

void Menu::menuPrincipal() {
	int opcion = 0;
	do {
		cout << "\n=== Menu Principal ===\n";
		cout << "1. Mostrar estacionamiento del primer plantel\n";
		cout << "2. Submenu personas (clientes y colaboradores)\n";
		cout << "3. Mostrar resumen de planteles\n";
		cout << "4. Salir\n";
		cout << "Seleccione una opcion: ";
		cin >> opcion;
		validarEntero(opcion);

		switch (opcion) {
		case 1: {
			NodoPl* primero = sucursalActual->getPlanteles()->getPrimero();
			if (primero) {
				Plantel* p = primero->getDato();
				cout << p->mostrarEstacionamiento(0) << endl;
			} else {
				cout << "No hay planteles registrados.\n";
			}
			break;
		}
		case 2:
			submenuPersonas();
			break;
		case 3:
			cout << sucursalActual->getPlanteles()->mostrarPlanteles() << endl;
			break;
		case 4:
			break;
		default:
			cout << "Opcion invalida.\n";
		}
	} while (opcion != 4);
}

void Menu::submenuPersonas() {
	int opcion = 0;
	do {
		cout << "\n--- Submenu Personas ---\n";
		cout << "1. Mostrar clientes\n";
		cout << "2. Mostrar colaboradores\n";
		cout << "3. Buscar cliente por ID\n";
		cout << "4. Buscar colaborador por ID\n";
		cout << "5. Eliminar cliente por ID\n";
		cout << "6. Volver\n";
		cout << "Seleccione una opcion: ";
		cin >> opcion;
		validarEntero(opcion);

		switch (opcion) {
		case 1:
			cout << sucursalActual->getClientes()->mostrarClientes() << endl;
			break;
		case 2:
			cout << sucursalActual->getColaboradores()->mostrarColaboradores() << endl;
			break;
		case 3: {
			string id;
			cout << "ID del cliente: ";
			cin >> id;
			if (auto c = sucursalActual->getClientes()->buscarCliente(id)) cout << c->toString() << endl; else cout << "No encontrado.\n";
			break;
		}
		case 4: {
			string id;
			cout << "ID del colaborador: ";
			cin >> id;
			if (auto c = sucursalActual->getColaboradores()->buscarColaborador(id)) cout << c->toString() << endl; else cout << "No encontrado.\n";
			break;
		}
		case 5: {
			string id;
			cout << "ID del cliente a eliminar: ";
			cin >> id;
			bool ok = sucursalActual->getClientes()->eliminarCliente(id);
			cout << (ok ? "Eliminado.\n" : "No se encontro.\n");
			break;
		}
		case 6:
			break;
		default:
			cout << "Opcion invalida.\n";
		}
	} while (opcion != 6);
}
