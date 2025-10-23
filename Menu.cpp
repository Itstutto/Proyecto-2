#include "Menu.h"
#include <iostream>
#include "Plantel.h"
#include "Carro.h"
#include "ClienteFisico.h"
#include "ClienteJuridico.h"
#include "Colaborador.h"
#include "ListaPlantel.h"

using namespace std;

Menu::Menu() {
	sucursales = new ListaSucursales();

}

Menu::~Menu()
{
	delete sucursales;
}

bool Menu::validarEntero(int& opcion) {
	if (cin.fail()) {
		cin.clear();
		cin.ignore(10000, '\n');
		opcion = 0;
		cout << "Entrada invalida. Intente de nuevo." << endl;
		system("cls");
		return true;
	}
	return false;
}

void Menu::inicializarDatos() {
	Sucursal* suc1 = new Sucursal(1);

	
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

	suc1->getPlanteles()->insertarFinal(plantel);

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

	suc1->getClientes()->insertarFinal(cf1);
	suc1->getClientes()->insertarFinal(cj1);
	suc1->getClientes()->insertarFinal(cf2);
	suc1->getClientes()->insertarFinal(cj2);

	// Colaboradores
	Colaborador* co1 = new Colaborador("Maria Lopez", "C1", string("01/01/2024"));
	Colaborador* co1_dup = new Colaborador("Maria Lopez", "C1", string("01/01/2024"));
	Colaborador* co2 = new Colaborador("Carlos Soto", "C2", string("15/05/2023"));


	suc1->getColaboradores()->insertarFinal(co1);
	suc1->getColaboradores()->insertarFinal(co1_dup);
	suc1->getColaboradores()->insertarFinal(co2);

	sucursales->insertarFinal(suc1);

	Cliente* prueba = dynamic_cast<Cliente*>(sucursales->obtenerSucursalPorIndice(0)->getColaboradores()->getPrimero()->getDato());
	if (prueba) {
		cout << prueba->getPaisResidencia() << endl;
	}
	else
	{
		cout << "No es un cliente" << endl;
	}
}

void Menu::iniciar() {
	inicializarDatos();
	menuPrincipal();
}

void Menu::menuPrincipal() {
	int opcion = 0; //se usa en TODOS los menus
	Sucursal* s = nullptr; // Sucursal seleccionada
	int enteros;
	string textos;
	char sn;

	do {
		cout << "\n================ DRT CAR ====================\n";
		cout << sucursales->mostrarSucursales(0);
		cin >> opcion;
		validarEntero(opcion);

		if(opcion==sucursales->getTam()+3){}
		else if (opcion >= 1 && opcion <= sucursales->getTam()) {
			s = sucursales->obtenerSucursalPorIndice(opcion - 1);
			
			
			do {
				cout << s->mostrarOpciones();
				cin >> opcion;
				validarEntero(opcion);
				switch (opcion) {
				case 1:
					cout << s->getClientes()->mostrarPersonas();
					break;
				case 2:
					cout << s->getColaboradores()->mostrarPersonas();
					break;
				case 3:
					cout << "Gestionar Planteles (funcionalidad no implementada)." << endl;
					break;
				case 4:
					cout << "Gestionar Contratos (funcionalidad no implementada)." << endl;
					break;
				case 5:
					break;
				default:
					system("cls");
					cout << "Opcion invalida. Intente de nuevo." << endl<<endl;
					break;
				}
			} while (opcion != 5);
			opcion = 0; // Reiniciar opcion para el menu principal
		}
		else if (opcion == sucursales->getTam() + 1) {
			Sucursal* nuevaSuc = new Sucursal();
			do {
				cout << "Ingrese el numero de la nueva sucursal: ";
				cin >> enteros;
			} while (validarEntero(enteros));
			if (sucursales->buscarSucursal(enteros)) {
				cout << "Sucursal con ese numero ya existe. Operacion cancelada." << endl;
				delete nuevaSuc;
				nuevaSuc = nullptr;

			}
			nuevaSuc->setNumeroSucursal(enteros);
			cout << "Esta seguro de crear la sucursal numero " << enteros << "? (s/n): ";
			cin >> sn;
			if (sn == 's' || sn == 'S') {
				if (sucursales->insertarFinal(nuevaSuc)) {
					cout << "Sucursal creada exitosamente." << endl;
				}
				else {
					cout << "Error: No se pudo crear la sucursal. Puede que ya exista una sucursal con ese numero." << endl;
					delete nuevaSuc;
					nuevaSuc = nullptr;
				}
			}
			else {
				cout << "Creacion de sucursal cancelada." << endl;
				delete nuevaSuc;
				nuevaSuc = nullptr;
			}

		}
		else if (opcion == sucursales->getTam() + 2) {
			cout << "Elija la sucursal a eliminar:"<<endl;
			cout << sucursales->mostrarSucursales(1);
			cin >> enteros;
			validarEntero(enteros);
			cout << "Esta seguro de eliminar la sucursal numero " << sucursales->obtenerSucursalPorIndice(enteros - 1)->getNumeroSucursal() << "? (Con esto elimina TODO (Planteles, Carros, Contratos, CLientes, etc)) (s/n): ";
			cin >> sn;
			if (sn == 's' || sn == 'S') {
				if (sucursales->eliminarSucursal(sucursales->obtenerSucursalPorIndice(enteros - 1)->getNumeroSucursal())) {
					cout << "Sucursal eliminada exitosamente." << endl;
				}
				else {
					cout << "Error: No se pudo eliminar la sucursal." << endl;
				}
			}
			else {
				cout << "Eliminacion de sucursal cancelada." << endl;
			}
		}
		else {
			cout << "Opcion invalida. Intente de nuevo."<<endl;
		}

	} while (opcion != sucursales->getTam()+3);
}


