#include "Menu.h"
#include <iostream>
#include "Plantel.h"
#include "Carro.h"
#include "ClienteFisico.h"
#include "ClienteJuridico.h"
#include "Colaborador.h"
#include "ListaPlantel.h"
#include "SolicitudAlquiler.h"
#include "ContratoAlquiler.h"
#include "SolicitudPendiente.h"

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

	Carro* carro1 = new Carro("123-ABC", "Corolla", "Toyota", "Madrid", "B1", 'B', 45.00);
	Carro* carro2 = new Carro("567-DEF", "Civic", "Honda", "Barcelona", "B1", 'B', 40.00);
	Carro* carro3 = new Carro("901-GHI", "Model S", "Tesla", "Valencia", "B2", 'A', 60.00);
	Carro* carro4 = new Carro("345-JKL", "F-150", "Ford", "Sevilla", "C1", 'C', 55.00);
	Carro* carro5 = new Carro("789-MNO", "Tucson", "Hyundai", "Bilbao", "B2", 'B', 50.00);
	Carro* carro6 = new Carro("234-PQR", "Golf", "Volkswagen", "Granada", "B1", 'B', 45.00);

	plantel->agregarCarro(carro1, 0);
	plantel->agregarCarro(carro2, 12);
	plantel->agregarCarro(carro3, 24);
	plantel->agregarCarro(carro4, 31);
	plantel->agregarCarro(carro5, 43);
	plantel->agregarCarro(carro6, 55);

	suc1->getPlanteles()->insertarFinal(plantel);

	// Transacciones de ejemplo
	string idSucursalStr = to_string(suc1->getNumeroSucursal());
	SolicitudAlquiler* sol1 = new SolicitudPendiente("S001", "111", "C1", idSucursalStr, "234-PQR", 5, "25/11/2025", "30/11/2025", 45.00, 225.00);
	suc1->getTransacciones()->insertarFinal(sol1);
	ContratoAlquiler* con1 = new ContratoAlquiler("C002", "333", "C2", idSucursalStr, "901-GHI", 10, "20/11/2025", "30/11/2025", 60.00, 600.00);
	suc1->getTransacciones()->insertarFinal(con1);

	// Bitacora: mover carro3 Disponible(1) -> Alquilado(2)
	carro3->setEstadosCarro(5, "SISTEMA"); // Revision -> Lavado
	carro3->setEstadosCarro(1, "SISTEMA"); // Lavado -> Disponible
	carro3->setEstadosCarro(2, "C2");      // Disponible -> Alquilado

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

	/*Cliente* prueba = dynamic_cast<Cliente*>(sucursales->obtenerSucursalPorIndice(0)->getColaboradores()->getPrimero()->getDato());
	if (prueba) {
		cout << prueba->getPaisResidencia() << endl;
	}
	else
	{
		cout << "No es un cliente" << endl;
	}*/
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

                case 4:// Inicia gestionar contratos/solicitudes --------------------------------------------------------------------
                    do {
                        system("cls"); // Limpiar antes de mostrar el menu
                        cout << "\n============= GESTION DE TRANSACCIONES ==============\n";
                        // Mostrar resumen de Solicitudes y Contratos
                        cout << s->getTransacciones()->mostrarTransacciones();
                        cout << "\n1. Crear Solicitud de Alquiler\n";
                        cout << "2. Ver Detalle y Gestionar Transaccion (Aprobar/Rechazar/Anular)\n";
                        cout << "3. Regresar\n";
                        cout << "Seleccione una opcion: ";
                        cin >> enteros; // Usar la variable 'enteros' para este submenú
                        
                        if (validarEntero(enteros)) continue;

                        switch (enteros) {
                        case 1: { // Crear Solicitud de Alquiler
                            system("cls");
                            cout << "\nFuncionalidad: Crear Solicitud (No implementada aún).\n";
                            system("pause");
                            break;
                        }
                        case 2: { // Ver Detalle y Gestionar Transaccion
                            system("cls");
                            // Mostrar nuevamente la lista antes de pedir el codigo
                            cout << s->getTransacciones()->mostrarTransacciones();
                            cout << "\nDigite el codigo de la transaccion (ej. S001 o C002): ";
                            cin >> textos; // Usar la variable 'textos' para el codigo
                            
                            SolicitudAlquiler* sol = s->getTransacciones()->buscarTransaccion(textos);

                            if (sol) {
                                // Inicia submenu de gestion de la transaccion
                                do {
                                    system("cls");
                                    cout << "\n========= DETALLE Y GESTION DE TRANSACCION =========\n";
                                    cout << sol->toString() << endl; // Muestra el detalle completo
                                    cout << "\n----------------------------------------------------\n";

                                    // Mostrar opciones de gestion segun el estado
                                    if (sol->getEstadoTransaccion() == 1) { // Solo si es Pendiente (1)
                                        cout << "1. Aprobar Solicitud (Convertir a Contrato)\n";
                                        cout << "2. Rechazar Solicitud\n";
                                        cout << "3. Anular Solicitud\n";
                                        cout << "4. Regresar\n";
                                    } else { // Si ya es Contrato (2), solo se puede anular o regresar
                                        cout << "1. No disponible (Ya es Contrato)\n";
                                        cout << "2. No disponible\n";
                                        cout << "3. Anular Contrato\n";
                                        cout << "4. Regresar\n";
                                    }
                                    cout << "Seleccione una opcion: ";
                                    cin >> opcion; // Usar la variable 'opcion' para este sub-submenu

                                    if (validarEntero(opcion)) continue;

                                    switch (opcion) {
                                    case 1: { // Aprobar o no disponible
                                        if (sol->getEstadoTransaccion() != 1) {
                                            cout << "Esta transaccion ya no es Pendiente y no puede ser Aprobada.\n";
                                            break;
                                        }
                                        
                                        // Lógica de Aprobación
                                        cout << "ID Colaborador que aprueba: ";
                                        cin >> textos; // Usar 'textos' para el ID del colaborador
                                        
                                        // NOTA IMPORTANTE: Buscar el Carro por placa y cambiar estado a Alquilado (2)
                                        // con carro->setEstadosCarro(2, textos) y convertir la Solicitud a Contrato.
                                        
                                        cout << "\nFuncionalidad: Aprobar solicitud. Estado de Carro y conversion de Solicitud (Pendiente de implementar logica).";
                                        break;
                                    }
                                    case 2: { // Rechazar o no disponible
                                         if (sol->getEstadoTransaccion() != 1) {
                                            cout << "Opcion no disponible para el estado actual de la transaccion.\n";
                                            break;
                                        }
                                        // Lógica de Rechazo: Cambiar estado de la Solicitud a 3 (Rechazada)
                                        cout << "\nFuncionalidad: Rechazar Solicitud y cambiar estado a 3 (Rechazada) (No implementada).\n";
                                        break;
                                    }
                                    case 3: { // Anular (Pendiente: Lógica de Carro a Disponible/Devuelto/etc.)
                                        // Lógica de Anulación: Cambiar estado de la Solicitud a 4 (Anulada)
                                        cout << "\nFuncionalidad: Anular Transaccion y cambiar estado a 4 (Anulada) (No implementada).\n";
                                        break;
                                    }
                                    case 4: // Regresar
                                        break;
                                    default:
                                        cout << "Opcion invalida.\n";
                                        break;
                                    }
                                    system("pause");
                                } while (opcion != 4);
                                opcion = 0; // Reiniciar 'opcion' para el menu de transacciones
                            } else {
                                system("cls");
                                cout << "ERROR: No se encontro ninguna transaccion con el codigo: " << textos << endl;
                                system("pause");
                            }
                            break;
                        }
                        case 3: // Regresar
							system("cls");
                            break;
                        default:
                            system("cls");
                            cout << "Opcion invalida. Intente de nuevo.\n";
                            system("pause");
                            break;
                        }
                    } while (enteros != 3);
                    opcion = 0; // Reiniciar 'opcion' para el menu de sucursal
                    break; // Termina gestionar contratos/solicitudes --------------------------------------------------------------------

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
			// Prompt robusto: repetir hasta que el entero sea valido y este en rango
			bool cancelar = false;
			while (true) {
				cout << "Elija la sucursal a eliminar:" << endl;
				cout << sucursales->mostrarSucursales(1);
				cin >> enteros;
				system("cls");
				if (validarEntero(enteros)) {
					continue; // reintentar si hubo error de entrada
				}
				int opcionSalir = sucursales->getTam() + 1;
				if (enteros == opcionSalir) { // usuario eligio salir
					cancelar = true;
					break;
				}
				if (enteros < 1 || enteros > sucursales->getTam()) {
					cout << "Opcion invalida. Intente de nuevo." << endl;
					continue; // reintentar si esta fuera de rango
				}
				break; // valido
			}

			if (!cancelar) {
				Sucursal* sel = sucursales->obtenerSucursalPorIndice(enteros);
				if (!sel) {
					cout << "Seleccion invalida. Intente de nuevo." << endl;
				}
				else {
					cout << "Esta seguro de eliminar la sucursal numero " << sel->getNumeroSucursal() << "? (Con esto elimina TODO (Planteles, Carros, Contratos, CLientes, etc)) (s/n): ";
			cin >> sn;
			if (sn == 's' || sn == 'S') {
						if (sucursales->eliminarSucursal(sel->getNumeroSucursal())) {
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
			}
			// si cancelar==true, simplemente volver al menu principal
		}//Termina eliminar sucursal--------------------------------------------------------------------
		else {
			cout << "Opcion invalida. Intente de nuevo."<<endl;
		}

	} while (opcion != sucursales->getTam()+3);
}


