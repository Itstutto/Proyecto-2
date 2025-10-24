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

bool Menu::validarFlotante(double& opcion) {
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
	Plantel* p = nullptr; // Plantel seleccionado

	Persona* per = nullptr; // Persona seleccionada (Cliente o Colaborador)
	Cliente* cli = nullptr; // Cliente seleccionado
	ClienteFisico* cfis = nullptr; // Cliente Fisico seleccionado
	ClienteJuridico* cjur = nullptr; // Cliente Juridico seleccionado
	Colaborador* colab = nullptr; // Colaborador seleccionado
	ListaClientes1* lc = nullptr; // Lista de clientes de la sucursal




	int enteros;
	string textos;
	char sn;

	do {
		cout << "\n================ DRT CAR ====================\n";
		cout << sucursales->mostrarSucursales(0);
		cin >> opcion;
		system("cls");
		validarEntero(opcion);

		if(opcion==sucursales->getTam()+3){}
		else if (opcion >= 1 && opcion <= sucursales->getTam()) {
			s = sucursales->obtenerSucursalPorIndice(opcion);
			
			
			do {
				cout << s->mostrarOpciones();
				cin >> opcion;
				system("cls");
				validarEntero(opcion);
				
				switch (opcion) {
				case 1:// Inicia gestionar clientes--------------------------------------------------------------------
					do {
						int tipoCliente;
						lc = s->getClientes();
						cout << lc->mostrarPersonas(0);
						cin >> opcion;
						system("cls");
						validarEntero(opcion);
						if (opcion >= 1 && opcion <= lc->getTam()) { 
							// Inicia Mostrar detalles del cliente seleccionado-----------------------------------------------------------------------------
							cli = dynamic_cast<Cliente*>(lc->obtenerPersonaPorIndice(opcion));
							do {
								do {
									cout << cli->mostrarCliente();
									cin >> opcion;
								} while (validarEntero(opcion));
								switch (opcion) {
								case 1:
									cout << "Modificar Cliente (funcionalidad no implementada)." << endl;
									break;
								case 2:
									cout << "Informacion del Cliente:" << endl;
									cout << cli->toString() << endl;
									break;
								case 3:
									cout << "Historial de Alquileres (funcionalidad no implementada)." << endl;
									break;
								case 4:
									break;

								}
							} while (opcion != 4);
							opcion = 0; // Reiniciar opcion para el menu de clientes
							system("pause");
							system("cls");
						}
						else if (opcion == lc->getTam() + 1) {
							cout << "Reporte clientes (funcionalidad no implementada)." << endl;
						}
						else if (opcion == lc->getTam() + 2) {
							do {
								cout << "Elija el tipo de cliente a agregar " << endl
									<< "1. Cliente Fisico" << endl
									<< "2. Cliente Juridico" << endl;
								cin >> tipoCliente;
								if (!validarEntero(tipoCliente) && (tipoCliente != 1 && tipoCliente != 2)) {
									cout << "Opcion invalida. Intente de nuevo." << endl;
									continue;
								}
							} while (validarEntero(tipoCliente));
							if (tipoCliente == 1) {
								cli= new ClienteFisico();
							}
							else {
								cli = new ClienteJuridico();
							}
							cout << "Digite la cedula " << (tipoCliente == 1 ? "fisica" : "juridica") << " del cliente: ";
							cin >> textos;
							if (lc->buscarPersona(textos)) {
								cout << "Cliente con esa cedula ya existe. Operacion cancelada." << endl;
								delete cli;
								cli = nullptr;
								continue;
							}
							cli->setId(textos);
							cout << "Digite el nombre del cliente: ";
							cin.ignore();
							getline(cin, textos);
							cli->setNombre(textos);
							cout << "Digite el pais de residencia del cliente: ";
							getline(cin, textos);
							cli->setPaisResidencia(textos);
							if (tipoCliente == 2) {
								cjur = dynamic_cast<ClienteJuridico*>(cli);
								cout << "Digite la actividad economica del cliente juridico: ";
								getline(cin, textos);
								cjur->setActividadEconomica(textos);
								double pct;
								do {
									cout << "Digite el porcentaje de descuento del cliente juridico: ";
									cin >> pct;
								} while (validarFlotante(pct));
								cjur->setPorcentajeDescuento(pct);
							}
							cout << cli->toString() << endl;
							cout << "Esta seguro de agregar este cliente? (s/n): ";
							cin >> sn;
							if (sn == 's' || sn == 'S') {
								if (lc->insertarFinal(cli)) {
									cout << "Cliente agregado exitosamente." << endl;
								}
								else {
									cout << "Error: No se pudo agregar el cliente. Puede que ya exista un cliente con esa cedula." << endl;
									//no se elimina cli porque el insertarFinal lo hace en caso de error
									cli = nullptr;
								}
							}
							else {
								cout << "Creacion de cliente cancelada." << endl;
								delete cli; // eliminar cliente creado
								cli = nullptr;
							}

							
						}
						else if (opcion == lc->getTam() + 3) {
							do {
								
								do
								{
									cout << "Elija el cliente a eliminar: " << endl;
									cout << lc->mostrarPersonas(1);
									cin >> opcion;
									system("cls");
								} while (validarEntero(opcion));

								if (opcion == lc->getTam() + 1); // Salir
								else if (opcion >= 1 && opcion <= lc->getTam()) {
									cli = dynamic_cast<Cliente*>(lc->obtenerPersonaPorIndice(opcion));
									cout << "Esta seguro de eliminar al cliente " << cli->getNombre() << " con ID " << cli->getId() << "? (s/n): ";
									cin >> sn;
									system("cls");
									if (sn == 's' || sn == 'S') {
										if (lc->eliminarPersona(cli->getId())) {
											cout << "Cliente eliminado exitosamente." << endl;
										}
										else {
											cout << "Error: No se pudo eliminar el cliente." << endl;
										}
									}
									else {
										cout << "Eliminacion de cliente cancelada." << endl;
									}
								}
								else {
									system("cls");
									cout << "Opcion invalida. Intente de nuevo." << endl<<endl;
								}

							} while (opcion != lc->getTam()+1);

						}
						else if (opcion == lc->getTam() + 4); // Salir
						else {
							system("cls");
							cout << "Opcion invalida. Intente de nuevo." << endl<<endl;
						}
					} while (opcion != lc->getTam()+4);
					opcion = 0; // Reiniciar opcion para el menu de sucursal
					break; // Termina gestionar clientes--------------------------------------------------------------------
				case 2:// Inicia gestionar colaboradores--------------------------------------------------------------------
						cout << s->getColaboradores()->mostrarPersonas(0);
						break;// Termina gestionar colaboradores--------------------------------------------------------------------
				case 3:// Inicia gestionar planteles--------------------------------------------------------------------
					cout << "Gestionar Planteles (funcionalidad no implementada)." << endl;
					break;// Termina gestionar planteles--------------------------------------------------------------------
				case 4:// Inicia gestionar contratos--------------------------------------------------------------------
					cout << "Gestionar Contratos (funcionalidad no implementada)." << endl;
					break;// Termina gestionar contratos--------------------------------------------------------------------
				case 5:// Regresar al menu principal
					break;
				default:
					system("cls");
					cout << "Opcion invalida. Intente de nuevo." << endl<<endl;
					break;
				}
			} while (opcion != 5);
			opcion = 0; // Reiniciar opcion para el menu principal
		}
		else if (opcion == sucursales->getTam() + 1) { //Inicia agregar sucursal--------------------------------------------------------------------
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
			else {
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

		} //Termina agregar sucursal--------------------------------------------------------------------
		else if (opcion == sucursales->getTam() + 2) {//Inicia eliminar sucursal--------------------------------------------------------------------
			do {
				cout << "Elija la sucursal a eliminar:" << endl;
				cout << sucursales->mostrarSucursales(1);
				cin >> enteros;
				system("cls");
				if (!validarEntero(enteros) && enteros<1 || enteros>sucursales->getTam()) {// Validar rango
					cout << "Opcion invalida. Intente de nuevo." << endl;
					continue;
				}
			}while(validarEntero(enteros));
			cout << "Esta seguro de eliminar la sucursal numero " << sucursales->obtenerSucursalPorIndice(enteros)->getNumeroSucursal() << "? (Con esto elimina TODO (Planteles, Carros, Contratos, CLientes, etc)) (s/n): ";
			cin >> sn;
			if (sn == 's' || sn == 'S') {
				if (sucursales->eliminarSucursal(sucursales->obtenerSucursalPorIndice(enteros)->getNumeroSucursal())) {
					cout << "Sucursal eliminada exitosamente." << endl;
				}
				else {
					cout << "Error: No se pudo eliminar la sucursal." << endl;
				}
			}
			else {
				cout << "Eliminacion de sucursal cancelada." << endl;
			}
		}//Termina eliminar sucursal--------------------------------------------------------------------
		else {
			cout << "Opcion invalida. Intente de nuevo."<<endl;
		}

	} while (opcion != sucursales->getTam()+3);
}


