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
	alquilados = new Plantel('X', 40, 40); // Plantel temporal para carros alquilados

}

Menu::~Menu()
{
	delete sucursales;
}



// Implementación de la nueva función auxiliar
void Menu::mostrarTransaccionesColaborador(Sucursal* s, Colaborador* colab) {
	int seleccion = 0;
	ListaSolicitudesContratos* lsc = s->getSolicitudes();
	
	do {
		system("cls");
		cout << "\n============= SOLICITUDES PENDIENTES GESTIONADAS POR " << colab->getNombre() << " ==============\n";
		
		// 1. Mostrar la lista filtrada
		cout << colab->mostrarSolicitudesPendientesGestionadas(lsc); 

		cout << "Seleccione el numero de la solicitud para gestionar o Regresar: ";
		cin >> seleccion;
		
		if (validarEntero(seleccion)) continue;
		
		// 2. Obtener la Solicitud seleccionada por el índice FILTRADO
		SolicitudAlquiler* sol = lsc->obtenerTransaccionFiltradaPorIndice(colab->getId(), seleccion);
		
		if (!sol) { 
			// Lógica para salir si se selecciona "Regresar" o es inválido
			// Calculamos la opción de Regresar dinámicamente sin acceder a nodos internos:
			int numSolicitudes = 0;
			while (lsc->obtenerTransaccionFiltradaPorIndice(colab->getId(), numSolicitudes + 1)) {
				numSolicitudes++;
			}
			int opcionRegresar = numSolicitudes + 1;
			
			if (seleccion == opcionRegresar) {
				break; // Salir del bucle principal
			}
			
			cout << "Opcion invalida. Intente de nuevo.\n";
			system("pause");
			continue;
		} 
		
		if (sol) {
			// 3. Entrar en el submenú de gestión
			int opcionGestion;
			string textos; // Para el ID del colaborador que aprueba
			
			do {
				system("cls");
				cout << "\n========= GESTION DE SOLICITUD #" << sol->getCodigoTransaccion() << " =========\n";
				cout << sol->toString() << endl;
				cout << "\n----------------------------------------------------\n";

				cout << "1. Aprobar Solicitud (Convertir a Contrato)\n";
				cout << "2. Rechazar Solicitud\n";
				cout << "3. Anular Solicitud\n";
				cout << "4. Regresar\n";

				cout << "Seleccione una opcion: ";
				cin >> opcionGestion;
				if (validarEntero(opcionGestion)) continue;

				switch (opcionGestion) {
					case 1: { // Aprobar y convertir (Lógica CRÍTICA)
						cout << colab->toString() << endl;
						cout << "ID Colaborador que aprueba la conversion (su ID): ";
						cin >> textos; 
						
						// LLAMADA A LA LÓGICA DE NEGOCIO EN SUCURSAL (Incluye la validación de carro alquilado)
						if (s->convertirSolicitudAContrato(sol->getCodigoTransaccionInt(), textos, s->getSolicitudes(), s->getContratos(), s->getClientes(), s->getColaboradores())) {
							cout << "Operacion de Aprobacion Exitosa.\n";
							seleccion = 0; // Fuerza la actualización de la lista
							opcionGestion = 4; // Salir del submenú de gestión
						} else {
							// Si falla por carro no disponible/eliminado, la solicitud se elimina, forzamos la salida.
							if (!s->getSolicitudes()->buscarTransaccionPorCodigo(sol->getCodigoTransaccionInt())) {
								seleccion = 0;
								opcionGestion = 4;
							}
						}
						break;
					}
					case 2: { // Rechazar
						sol->setEstadoTransaccion(3); 
						
						// Actualizar historiales y eliminar de la lista principal
						Cliente* cli = dynamic_cast<Cliente*>(sol->getCliente());
						Colaborador* col = dynamic_cast<Colaborador*>(sol->getColaborador());
						if (cli) cli->getHistorial()->buscarTransaccionPorCodigo(sol->getCodigoTransaccionInt())->setEstadoTransaccion(3);
						if (col) col->getHistorial()->buscarTransaccionPorCodigo(sol->getCodigoTransaccionInt())->setEstadoTransaccion(3);

						lsc->eliminarTransaccionPorCodigo(sol->getCodigoTransaccionInt());
						cout << "\nSOLICITUD RECHAZADA Y ELIMINADA exitosamente.\n";
						seleccion = 0; // Fuerza la actualización de la lista
						opcionGestion = 4;
						break;
					}
					case 3: { // Anular
						sol->setEstadoTransaccion(4); // 4 = Anulada
						cout << "\nSOLICITUD ANULADA exitosamente.\n";
						break;
					}
					case 4: // Regresar
						break;
					default:
						cout << "Opcion invalida.\n";
						break;
				}
				system("pause");
			} while (opcionGestion != 4);
		}

	} while (seleccion != 0); 
}


// Nueva función auxiliar (Ver Solicitudes Pendientes del Cliente)
void Menu::mostrarTransaccionesCliente(Sucursal* s, Cliente* cli) {
	int seleccion = 0;
	ListaSolicitudesContratos* lsc = s->getSolicitudes();
	
	do {
		system("cls");
		cout << "\n============= SOLICITUDES PENDIENTES REALIZADAS POR " << cli->getNombre() << " ==============\n";
		
		// 1. Mostrar la lista filtrada
		cout << cli->mostrarSolicitudesPendientesRealizadas(lsc); 

		cout << "Seleccione el numero de la solicitud para gestionar o Regresar: ";
		cin >> seleccion;
		
		if (validarEntero(seleccion)) continue;
		
		// 2. Obtener la Solicitud seleccionada por el índice FILTRADO
		SolicitudAlquiler* sol = lsc->obtenerTransaccionFiltradaPorIndiceCliente(cli->getId(), seleccion);
		
		if (!sol) { 
			// Lógica para salir si se selecciona "Regresar" o es inválido
			int numSolicitudes = 0;
			while (lsc->obtenerTransaccionFiltradaPorIndiceCliente(cli->getId(), numSolicitudes + 1)) {
				numSolicitudes++;
			}
			int opcionRegresar = numSolicitudes + 1;
			
			if (seleccion == opcionRegresar) {
				break; // Salir del bucle principal
			}
			
			cout << "Opcion invalida. Intente de nuevo.\n";
			system("pause");
			continue;
		} 
		

		if (sol) {
			// 3. Entrar en el submenú de gestión (Solo Anular)
			int opcionGestion;
			
			do {
				system("cls");
				cout << "\n========= GESTION DE SOLICITUD #" << sol->getCodigoTransaccion() << " =========\n";
				cout << sol->toString() << endl;
				cout << "\n----------------------------------------------------\n";

				cout << "1. Anular Solicitud (Cancelacion por el Cliente)\n";
				cout << "2. Regresar\n";

				cout << "Seleccione una opcion: ";
				cin >> opcionGestion;
				if (validarEntero(opcionGestion)) continue;

				switch (opcionGestion) {
					case 1: { // Anular
						char sn;
						cout << "Esta seguro de ANULAR la Solicitud " << sol->getCodigoTransaccion() << "? (s/n): ";
						cin >> sn;
						
						if (sn == 's' || sn == 'S') {
							sol->setEstadoTransaccion(4); // 4 = Anulada
							
							// Actualizar historiales a Anulada (4)
							Colaborador* col = dynamic_cast<Colaborador*>(sol->getColaborador());
							cli->getHistorial()->buscarTransaccionPorCodigo(sol->getCodigoTransaccionInt())->setEstadoTransaccion(4);
							if (col) col->getHistorial()->buscarTransaccionPorCodigo(sol->getCodigoTransaccionInt())->setEstadoTransaccion(4);

							lsc->eliminarTransaccionPorCodigo(sol->getCodigoTransaccionInt());
							cout << "\nSOLICITUD ANULADA Y ELIMINADA exitosamente.\n";
							seleccion = 0; // Fuerza la actualización de la lista
							opcionGestion = 2; // Salir del submenú de gestión
						}
						break;
					}
					case 2: // Regresar
						break;
					default:
						cout << "Opcion invalida.\n";
						break;
				}
				system("pause");
			} while (opcionGestion != 2);
		}

	} while (seleccion != 0); 
}


void Menu::gestionarTransacciones(ListaSolicitudesContratos* lsc)
{
	int enteros = 0;
	int opcion = 0;
	char sn;
	string textos;
	do {
		do {
			cout << lsc->mostrarTransacciones();
			cin >> enteros;
			if (enteros<1 || enteros>lsc->getTam() + 1) {
				cout << "Opcion invalida. Intente de nuevo." << endl;
				continue;
			}
		} while (validarEntero(enteros));

		if (enteros == lsc->getTam() + 1);
		else {
			SolicitudAlquiler* sol = lsc->buscarTransaccion(enteros);
			if (sol) {
				// Inicia submenu de gestion de la transaccion
				do {
					system("cls");
					if (!sol) break; //Solicitud eliminada, sale de bucle
					cout << "\n========= DETALLE Y GESTION DE TRANSACCION =========\n";
					cout << sol->toString() << endl; // Muestra el detalle completo
					cout << "\n----------------------------------------------------\n";

					// Mostrar opciones de gestion segun el estado
					if (sol->getEstadoTransaccion() == 1) { // Solo si es Pendiente (1)
						cout << "1. Aprobar Solicitud (Convertir a Contrato)\n";
						cout << "2. Rechazar Solicitud\n";
						cout << "3. Anular Solicitud\n";
						cout << "4. Regresar\n";
					}
					else { // Si ya NO es Pendiente (incluye Contrato 2, Rechazada 3, Anulada 4)
						ContratoAlquiler* con = dynamic_cast<ContratoAlquiler*>(sol);
						if (con) { // ES UN CONTRATO ACTIVO (Estado Transacción = 2)
							do {
								system("cls");
								cout << "\n========= GESTION DE CONTRATO ACTIVO =========\n";
								cout << "Estado Operativo Actual: " << con->getEstadoDetalladoStr() << "\n";
								cout << "\n----------------------------------------------------\n";

								cout << (con->getEstadoDetallado()==2 ? "1. Ejecutar Contrato\n" : "1. Registrar Devolucion y Finalizar Contrato (NO USAR INCOMPLETA)\n" );
								cout << "2. Anular Contrato\n";
								cout << "3. Ver Historial de Carro (Bitacora)\n";
								cout << "4. Regresar\n";

								cout << "Seleccione una opcion: ";
								cin >> opcion;

								if (validarEntero(opcion)) continue;

								switch (opcion) {
									case 1: {
										if (con->getEstadoDetallado() == 2) {
											cout << "Esta seguro que desea ejecutar el contrato? s/n: ";
											cin >> sn;
											if (sn == 's' || sn == 'S') {

												con->setEstadoDetallado(1);
												sucursales->alquilarCarro(alquilados, con->getCarro()->getPlaca());
												cout << "Contrato ejecutado" << endl;

												
											}
											else {
												cout << "El contrato NO fue ejecutado" << endl;
											}

											
										}
										else {
											stringstream s;

											cout << "Ingrese la placa del vehiculo: ";
											cin >> textos;
											if (textos != con->getCarro()->getPlaca()) {
												cout << "La placa ingresada no concuerda con la placa del vehiculo ";
											}
											else {
												do {
													cout << "Digite los dias que se utilizo el vehiculo: ";
													cin >> enteros;
													system("cls");
												} while (validarEntero(enteros) || enteros < 0);
												s << "Dias utilizado: " << enteros;
											}


											
											// Lógica pendiente:
											// 1. Pedir dias utilizados.
											// 2. Calcular diferencia de dias vs. diasAlquiler.
											// 3. Aplicar multa/reintegro (70% del diario por dia anticipado).
											// 4. Actualizar el Contrato: con->setEstadoDetallado(3, "Finalizado [detalle]");
											// 5. Actualizar el Carro: Buscar Carro por Placa y carro->setEstadosCarro(3, con->getIdColaborador()); // Devuelto
										}
										break;
									}
									case 2: {
										// Solo se debería anular si el estado detallado es "Pendiente de Ejecución" (2)
										if (con->getEstadoDetallado() != 2) {
											cout << "ADVERTENCIA: Solo los contratos 'Pendiente de Ejecucion' pueden anularse facilmente.\n";
											cout << "NO se puede anular un contrato si esta en ejecucion";
											break;
										}
										cout << "Esta seguro de ANULAR el Contrato " << con->getCodigoTransaccion() << "? (s/n): ";
										cin >> sn;
										if (sn == 's' || sn == 'S') {
											// Implementación real: cambiar estado base a 4 (Anulada)
											con->setEstadoTransaccion(4);
											// Lógica pendiente: actualizar estado del carro si aplica
											cout << "\nCONTRATO ANULADO. [Logica de Carro Pendiente].\n";
										}
										break;
									}
									case 3: {
										cout << "\nFuncionalidad: Mostrar Bitacora del Carro (Se necesita buscar el Carro por Placa primero).\n";
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
							opcion = 4; // salir del bucle de detalle superior
							continue; // saltar el prompt general
						}
						else { // Si es Rechazada (3) o Anulada (4)
							cout << "Esta transaccion ya no es gestionable (Rechazada o Anulada).\n";
							system("pause");
							opcion = 4; // salir del bucle de detalle superior
							continue; // saltar el prompt general
						}
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
							if (sol->getCarro()->getCategoria() == '0') {
								cout << "El carro asociado ha sido eliminado o no es valido. Se eliminara la solicitud\n";
								Cliente* cli = dynamic_cast<Cliente*>(sol->getCliente());
								Colaborador* col = dynamic_cast<Colaborador*>(sol->getColaborador());
								cli->getHistorial()->buscarTransaccionPorCodigo(sol->getCodigoTransaccionInt())->setEstadoTransaccion(3); // Actualizar historial cliente
								col->getHistorial()->buscarTransaccionPorCodigo(sol->getCodigoTransaccionInt())->setEstadoTransaccion(3); // Actualizar historial colaborador
								lsc->eliminarTransaccionPorCodigo(sol->getCodigoTransaccionInt()); // Eliminar de la lista general
								opcion = 4; //Obliga a salir del menu
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
						case 2: { // Rechazar Solicitud
							if (sol->getEstadoTransaccion() != 1) {
								cout << "Opcion no disponible para el estado actual de la transaccion.\n";
								break;
							}
							// Implementación real: cambiar estado a 3 (Rechazada)
							sol->setEstadoTransaccion(3);
							cout << "\nSOLICITUD RECHAZADA exitosamente.\n";
							cout << "Nota: En el cliente " << sol->getCliente()->getNombre() << " puede ver la solicitud RECHAZADA\n";
							Cliente* cli = dynamic_cast<Cliente*>(sol->getCliente());
							Colaborador* col = dynamic_cast<Colaborador*>(sol->getColaborador());
							cli->getHistorial()->buscarTransaccionPorCodigo(sol->getCodigoTransaccionInt())->setEstadoTransaccion(3); // Actualizar historial cliente
							col->getHistorial()->buscarTransaccionPorCodigo(sol->getCodigoTransaccionInt())->setEstadoTransaccion(3); // Actualizar historial colaborador
							lsc->eliminarTransaccionPorCodigo(sol->getCodigoTransaccionInt()); // Eliminar de la lista general
							opcion = 4; //Obliga a salir del menu
							break;
						}
						case 3: { // Anular Solicitud
							// Implementación real: cambiar estado a 4 (Anulada)
							sol->setEstadoTransaccion(4);
							cout << "\nSOLICITUD ANULADA exitosamente.\n";
							// Nota: Lógica de Carro (si aplica) pendiente de implementar
							cout << "Nota: En el cliente " << sol->getCliente()->getNombre() << " puede ver la solicitud RECHAZADA\n";
							Cliente* cli = dynamic_cast<Cliente*>(sol->getCliente());
							Colaborador* col = dynamic_cast<Colaborador*>(sol->getColaborador());
							cli->getHistorial()->buscarTransaccionPorCodigo(sol->getCodigoTransaccionInt())->setEstadoTransaccion(3); // Actualizar historial cliente
							col->getHistorial()->buscarTransaccionPorCodigo(sol->getCodigoTransaccionInt())->setEstadoTransaccion(3); // Actualizar historial colaborador
							lsc->eliminarTransaccionPorCodigo(sol->getCodigoTransaccionInt()); // Eliminar de la lista general
							opcion = 4; //Obliga a salir del menu
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
			}
			else {
				system("cls");
				cout << "ERROR al encontrar la solicitud ";
				system("pause");
			}
		}


	} while (enteros != lsc->getTam() + 1);
}

bool Menu::validarEntero(int& opcion) {
	if (cin.fail()) {
		cin.clear();
		cin.ignore(10000, '\n');
		opcion = 0;
		cout << "Entrada invalida. Intente de nuevo." << endl;
		system("pause");
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

	plantel->agregarCarro(carro1, 0, 0);
	plantel->agregarCarro(carro2, 1, 2);
	plantel->agregarCarro(carro3, 2, 4);
	plantel->agregarCarro(carro4, 3, 1);
	plantel->agregarCarro(carro5, 4, 3);
	plantel->agregarCarro(carro6, 5, 5);

	suc1->getPlanteles()->insertarFinal(plantel);


	// Bitacora: mover carro3 Disponible(1) -> Alquilado(2)
	carro3->setEstadosCarro(5, "SISTEMA"); // Revision -> Lavado
	carro3->setEstadosCarro(1, "SISTEMA"); // Lavado -> Disponible
	carro3->setEstadosCarro(2, "C2");      // Disponible -> Alquilado

	carro1->setEstadosCarro(5, "SISTEMA"); // Revision -> Lavado
	carro1->setEstadosCarro(1, "SISTEMA"); // Lavado -> Disponible

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

	// Solicitudes y Contratos
	SolicitudAlquiler* sol1 = new SolicitudPendiente(cf1, co1, carro1, 5, 12062024, 17062024, 45.00, 225.00);
	SolicitudAlquiler* sol2 = new SolicitudPendiente(cj1, co2, carro4, 3, 15062024, 18062024, 55.00, 165.00); // no se agrega a solicitudes porque se aprueba de una vez
	SolicitudAlquiler* sol3 = new ContratoAlquiler(*sol2); // Contrato basado en la solicitud aprobada
	suc1->getSolicitudes()->insertarFinal(sol1);
	cf1->getHistorial()->insertarFinal(new SolicitudPendiente(*sol1)); 
	co1->getHistorial()->insertarFinal(new SolicitudPendiente(*sol1));
	suc1->getContratos()->insertarFinal(sol3);
	


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
	Carro* car = nullptr; // Carro seleccionado
	ListaPlantel* lp = nullptr; // Lista de planteles de la sucursal
	Colaborador* colab = nullptr; // Colaborador seleccionado
	ListaClientes1* lc = nullptr; // Lista de clientes de la sucursal
	ListaColaboradores1* lcol = nullptr; // Lista de colaboradores de la sucursal
	ListaSolicitudesContratos* lsc = nullptr; // Lista de solicitudes/contratos de la sucursal
	SolicitudAlquiler* sol = nullptr; // Solicitud seleccionada



	int enteros;
	string textos;
	char carac;
	char sn;

	do {
		cout << "\n================ DRT CAR ====================\n";
		cout << sucursales->mostrarSucursales(0);
		cin >> opcion;
		system("cls");
		validarEntero(opcion);

		if (opcion == sucursales->getTam() + 3) {}
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
								system("cls");
								cout << "\nCliente: " << cli->getNombre() << " (ID: " << cli->getId() << ")\n";
								cout << "----------------------------------------------------\n";
								// Usar el método actualizado de Cliente:
								cout << cli->mostrarCliente(); // Ahora muestra 1-4 y 5. Regresar
								
								cout << "Seleccione una opcion: ";
								cin >> opcion;
														
								if (validarEntero(opcion)) continue; // Volver al inicio del do-while si es inválido
														
								switch (opcion) {
								case 1: { // Modificar informacion del cliente-----------------------------------------------------------------------------
									bool tipoCliente = dynamic_cast<ClienteFisico*>(cli) != nullptr; // true si es ClienteFisico, false si es ClienteJuridico
									int limite = tipoCliente ? 4 : 6; // Numero de opciones segun el tipo de cliente
									int opcionModificar;
									do {
										do {
											system("cls");
											cout << cli->mostrarModificar() << endl;
											cout << "Seleccione la opcion a modificar (o " << limite << " para regresar): ";
											cin >> opcionModificar;
										} while (validarEntero(opcionModificar));

										if (opcionModificar > limite) {
											cout << "Opcion invalida. Intente de nuevo." << endl;
											system("pause");
											continue;
										}
										if (opcionModificar == limite); // Salir del bucle de modificacion
										else {
											switch (opcionModificar) { // Usar opcionModificar para evitar conflictos con la opcion principal
											case 1:
												cout << "Digite el nuevo nombre del cliente: ";
												cin.ignore();
												getline(cin, textos);
												cli->setNombre(textos);
												cout << "Nombre actualizado exitosamente." << endl;
												break;
											case 2:
												cout << "Digite la nueva cedula del cliente: ";
												cin >> textos;
												if (lc->buscarPersona(textos)) {
													cout << "Cliente con esa cedula ya existe. Operacion cancelada." << endl;
													system("pause");
													continue;
												}
												cli->setId(textos);
												cout << "Cedula actualizada exitosamente." << endl;
												break;
											case 3:
												cout << "Digite el nuevo pais de residencia del cliente: ";
												cin.ignore();
												getline(cin, textos);
												cli->setPaisResidencia(textos);
												cout << "Pais de residencia actualizado exitosamente." << endl;
												break;
											case 4:
												if (!tipoCliente) {
													cjur = dynamic_cast<ClienteJuridico*>(cli);
													cout << "Digite la nueva actividad economica del cliente juridico: ";
													cin.ignore();
													getline(cin, textos);
													cjur->setActividadEconomica(textos);
													cout << "Actividad economica actualizada exitosamente." << endl;
												}
												break;
											case 5:
												if (!tipoCliente) {
													cjur = dynamic_cast<ClienteJuridico*>(cli);
													double pct;
													do {
														cout << "Digite el nuevo porcentaje de descuento del cliente juridico: ";
														cin >> pct;
													} while (validarFlotante(pct));
													cjur->setPorcentajeDescuento(pct);
													cout << "Porcentaje de descuento actualizado exitosamente." << endl;
												}
												break;
											}
											system("pause");
										}

									} while (opcionModificar != limite);
									break;
								}	
								case 2:
									cout << "Informacion del Cliente:" << endl;
									cout << cli->toString() << endl;
									system("pause");
									break;
								case 3:
									cout << cli->getHistorial()->mostrarHistorialCompletado() << endl;
									system("pause");
									break;
								case 4: // NUEVA OPCION: Ver Solicitudes Pendientes
									mostrarTransaccionesCliente(s, cli);
									break;
								case 5: // Regresar (Opción anterior era 4)
									break;
								default:
									cout << "Opcion invalida. Intente de nuevo." << endl;
									system("pause");
									break;

								}
							} while (opcion != 5); // Salir con 5
							opcion = 0; // Reiniciar opcion para el menu de clientes
							system("cls");
						}
						
						// REPORTE DE CLIENTES 
						else if (opcion == lc->getTam() + 1) { 
							cout << lc->generarReporteClientes() << endl; // Llama a la nueva función de reporte
							system("pause");
						}
						
						// AGREGAR NUEVO CLIENTE 
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
								cli = new ClienteFisico();
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
						
						// ELIMINAR CLIENTE 
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
									
									if (s->getSolicitudes()->transaccionesCliente(cli->getId()) || s->getContratos()->transaccionesCliente(cli->getId())) {
										system("cls");
										cout << "No se puede eliminar al cliente " << cli->getNombre() << " con ID " << cli->getId() << " porque tiene solicitudes o contratos asociados." << endl;
										continue;
									}
									
									cout << "Esta seguro de eliminar al cliente " << cli->getNombre() << " con ID " << cli->getId() << "? (s/n): ";
									cin >> sn;
									system("cls");
									if (sn == 's' || sn == 'S') {
										// Eliminar cliente de solicitudes, contratos y colaboradores MUY IMPORTANTE
										s->getSolicitudes()->clienteEliminado(cli->getId());
										s->getContratos()->clienteEliminado(cli->getId());
										s->getColaboradores()->eliminarClienteHistorial(cli->getId());
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
									cout << "Opcion invalida. Intente de nuevo." << endl << endl;
								}

							} while (opcion != lc->getTam() + 1);

						}
						else if (opcion == lc->getTam() + 4); // Salir
                        
                        // Manejo de opción inválida
                        else {
                            system("cls");
                            cout << "Opcion invalida. Intente de nuevo." << endl << endl;
                        }
					} while (opcion != lc->getTam() + 4);
					opcion = 0; // Reiniciar opcion para el menu de sucursal
                        break; // Termina gestionar clientes--------------------------------------------------------------------

                case 2:// Inicia gestionar colaboradores--------------------------------------------------------------------
					lcol = s->getColaboradores();
					do {
						do {
							cout << s->getColaboradores()->mostrarPersonas(0);
							cin >> opcion;
						} while (validarEntero(opcion));
						if (opcion >= 1 && opcion <= lcol->getTam()) {
							// Inicia Mostrar detalles del colaborador seleccionado-----------------------------------------------------------------------------
							colab = dynamic_cast<Colaborador*>(lcol->obtenerPersonaPorIndice(opcion));
							
							do { // Submenu de Detalle de Colaborador (NUEVO BUCLE)
								system("cls");
								cout << "\nColaborador: " << colab->getNombre() << " (ID: " << colab->getId() << ")\n";
								cout << "----------------------------------------------------\n";
								cout << "1. Ver Informacion Detallada\n";
								cout << "2. Ver Solicitudes Pendientes Gestionadas\n"; 
								cout << "3. Regresar\n";
								

								cout << "Seleccione una opcion: ";
								cin >> enteros; 
								if (validarEntero(enteros)) continue;
								
								switch (enteros) {
									case 1:
										cout << "Informacion del Colaborador:" << endl;
										cout << colab->toString() << endl;
										system("pause");
										break;
									case 2: // GESTION DE SOLICITUDES DEL COLABORADOR
										mostrarTransaccionesColaborador(s, colab); // Llamada a la nueva función
										break;
									case 3:
										break; 
									default:
										cout << "Opcion invalida.\n";
										system("pause");
										break;
								}
							} while (enteros != 3);
							opcion = 0; // reinicia para el menu
							system("cls"); 
						}
						else if (opcion == lcol->getTam() + 1) {
							colab = new Colaborador();
							cout << "Digite id del colaborador: ";
							cin >> textos;
							if (lcol->buscarPersona(textos)) {
								cout << "Colaborador con ese ID ya existe. Operacion cancelada." << endl;
								delete colab;
								colab = nullptr;
								continue;
							}
							colab->setId(textos);
							cout << "Digite el nombre del colaborador: ";
							cin.ignore();
							getline(cin, textos);
							colab->setNombre(textos);
							do {
								cout << "Digite la fecha de ingreso del colaborador (DD/MM/AAAA): ";
								cin >> enteros;
							} while (validarEntero(enteros));
							colab->setFechaIngreso(enteros);
							cout << colab->toString() << endl;
							cout << "Esta seguro de agregar este colaborador? (s/n): ";
							cin >> sn;
							if (sn == 's' || sn == 'S') {
								system("cls");
								if (lcol->insertarFinal(colab)) {
									cout << "Colaborador agregado exitosamente." << endl;
								}
								else {
									cout << "Error: No se pudo agregar el colaborador. Puede que ya exista un colaborador con ese ID." << endl;
									//no se elimina colab porque el insertarFinal lo hace en caso de error
									colab = nullptr;
								}
							}
							else {
								cout << "Creacion de colaborador cancelada." << endl;
								delete colab; // eliminar colaborador creado
								colab = nullptr;
							}


							
						}
						else if (opcion == lcol->getTam() + 2) {
							do {
								do {
									cout << "Elija el colaborador a eliminar: " << endl;
									cout << lcol->mostrarPersonas(1);
									cin >> opcion;
									system("cls");
								} while (validarEntero(opcion));

								if (opcion == lcol->getTam() + 1); // Salir
								else if (opcion<1 || opcion>lcol->getTam() + 1) {
									cout << "Opcion invalida. Intente de nuevo." << endl << endl;
									continue;
								}
								else {
									colab = dynamic_cast<Colaborador*>(lcol->obtenerPersonaPorIndice(opcion));
									if (s->getSolicitudes()->transaccionesColaborador(colab->getId()) || s->getContratos()->transaccionesColaborador(colab->getId())) {
										system("cls");
										cout << "No se puede eliminar al colaborador " << colab->getNombre() << " con ID " << colab->getId() << " porque tiene solicitudes o contratos asociados." << endl;
										continue;
									}
									cout << "Esta seguro de eliminar al colaborador " << colab->getNombre() << " con ID " << colab->getId() << "? (s/n): ";
									cin >> sn;
									system("cls");
									if (sn == 's' || sn == 'S') {
										// Eliminar colaborador de solicitudes y contratos MUY IMPORTANTE
										s->getSolicitudes()->colaboradorEliminado(colab->getId());
										s->getContratos()->colaboradorEliminado(colab->getId());
										s->getClientes()->eliminarColaboradorHistorial(colab->getId());
										if (lcol->eliminarPersona(colab->getId())) {
											cout << "Colaborador eliminado exitosamente." << endl;
										}
										else {
											cout << "Error: No se pudo eliminar el colaborador." << endl;
										}
									}
									else {
										cout << "Eliminacion de colaborador cancelada." << endl;
									}
								}
							} while (opcion!= lcol->getTam()+1);
						}
						else if (opcion == lcol->getTam() + 3); // Salir
						else {
							system("cls");
							cout << "Opcion invalida. Intente de nuevo." << endl << endl;
						}
					} while (opcion != lcol->getTam() + 3);
					opcion = 0; //Reinicia opcion
					break;// Termina gestionar colaboradores--------------------------------------------------------------------

				case 3:// Inicia gestionar planteles--------------------------------------------------------------------
					lp = s->getPlanteles();
					
					do {
						do {
							cout << lp->mostrarListaPlanteles(0);
							cin >> opcion;
							system("cls");
						} while (validarEntero(opcion));
						if (opcion == lp->getTam() + 4); // Salir
						else if (opcion >= 1 && opcion <= lp->getTam()) {
							// Inicia Mostrar detalles del plantel seleccionado-----------------------------------------------------------------------------

							p = lp->buscarPlantel(opcion);
							do {
								do {
									cout << p->mostrarPlantel();
									cin >> opcion;
								} while (validarEntero(opcion));
								switch (opcion) {
								case 1:
									cout << p->mostrarEstacionamiento(0);
									break;
								case 2: {// Ver carro especifico
									do {
										cout << p->mostrarEstacionamiento(0);
										cout << "Digite la placa del carro a ver: ";
										cin >> textos;
										car = p->getCarroxPlaca(textos);
										system("cls");
										if (!car) cout << "No se encontro un carro con esa placa. Intente de nuevo." << endl;
									} while (!car);
									cout << "Informacion del Carro:" << endl;
									cout << car->toString() << endl;
									system("pause");
									break;
								}
								case 3:
									
									cout << "Digite la placa del carro a agregar: ";
									cin >> textos;
									if (s->buscarCarroPorPlaca(textos)) {
										cout << "Carro con esa placa ya existe en el plantel. Operacion cancelada." << endl;
										continue;
									}
									car = new Carro();
									car->setPlaca(textos);
									cout << "Digite la marca del carro: ";
									cin.ignore();
									getline(cin, textos);
									car->setMarca(textos);
									cout << "Digite el modelo del carro: ";
									getline(cin, textos);
									car->setModelo(textos);
									cout << "Digite el tipo de licencia requerida (A, B, C): ";
									cin >> textos;
									car->setTipoLicencia(textos);
									cout << "Digite la categoria del carro (A, B, C): ";
									cin >> carac;
									car->setCategoria(carac);
									int fila, columna;
									do {
										cout << p->mostrarEstacionamiento(0);
										do {
											
											cout << "Digite la posicion donde desea agregar el carro ";
											cout << "Ubicaciones recomendadas: " << p->posicionesRecomendadas() << endl;
											cout << "Fila: ";
											cin >> fila;

										} while (validarEntero(fila));
										
										do {
											cout << "Columna: ";
											cin >> columna;
										} while (validarEntero(columna));

										if (!p->esPosicionValida(fila, columna)) {
											system("cls");
											cout << "Posicion invalida o ya ocupada. Intente de nuevo." << endl;
										}

									} while (!p->esPosicionValida(fila, columna));
									car->setUbicacion("(Asignada al agregar carro)");
									cout << car->toString() << endl;
									cout << "Esta seguro de agregar este carro en la posicion (" << fila << ", " << columna << ")? (s/n): ";
									cin >> sn;
									if (sn == 's' || sn == 'S') {
										system("cls");
										if (p->agregarCarro(car, fila, columna)) {
											cout << "Carro agregado exitosamente." << endl;
										}
										else {
											cout << "Error: No se pudo agregar el carro. Puede que ya exista un carro con esa placa." << endl;
											//no se elimina car porque el agregarCarro lo hace en caso de error
											car = nullptr;
										}
									}
									else {
										cout << "Creacion de carro cancelada." << endl;
										delete car; // eliminar carro creado
										car = nullptr;
									}
									break;
								case 4:
									do {
										cout << p->mostrarEstacionamiento(0);
										cout << "Digite la placa del carro a eliminar: ";
										cin >> textos;
										car = p->getCarroxPlaca(textos);
									} while (!car);
									if(car->getEstadoCarro() == "Alquilado") {
										cout << "No se puede eliminar el carro porque esta alquilado. Operacion cancelada." << endl;
										continue;
									}
									cout << "Esta seguro de eliminar el carro con placa " << car->getPlaca() << "? (s/n): ";
									cin >> sn;
									if (sn == 's' || sn == 'S') {
										system("cls");
										// Eliminar carro de solicitudes, contratos, clientes y colaboradores MUY IMPORTANTE
										lsc = s->getSolicitudes();
										lsc->vehiculoEliminado(car->getPlaca());
										s->getClientes()->vehiculoEliminado(car->getPlaca());
										s->getColaboradores()->vehiculoEliminado(car->getPlaca());

										if (p->eliminarCarro(car->getPlaca())) {
											cout << "Carro eliminado exitosamente." << endl;
										}
										else {
											cout << "Error: No se pudo eliminar el carro." << endl;
										}
									}
									else {
										cout << "Eliminacion de carro cancelada." << endl;
									}
								case 5:
									break; // Regresar
								default:
									cout << "Opcion invalida. Intente de nuevo." << endl;
									break;
								}
							} while (opcion != 5);
							opcion = 0; // Reiniciar opcion para el menu de planteles
						}
						else if (opcion == lp->getTam() + 1) {
							p = new Plantel();
							cout << "Digite el identificador del plantel (A-Z): ";
							cin >> carac;
							if (lp->buscarPlantel(carac)) {
								cout << "Plantel con ese identificador ya existe. Operacion cancelada." << endl;
								continue;
							}
							int filas, columnas;
							do {
								cout << "Digite el numero de filas del plantel: ";
								cin >> filas;
							} while (validarEntero(filas) || filas <= 0);
							do {
								cout << "Digite el numero de columnas del plantel: ";
								cin >> columnas;
							} while (validarEntero(columnas) || columnas <= 0);
							p = new Plantel(carac, filas, columnas);
							cout << p->mostrarEstacionamiento(0);
							cout << "Esta seguro de agregar este plantel? (s/n): ";
							cin >> sn;
							if (sn == 's' || sn == 'S') {
								system("cls");
								if (lp->insertarFinal(p)) {
									cout << "Plantel agregado exitosamente." << endl;
								}
								else {
									cout << "Error: No se pudo agregar el plantel. Puede que ya exista un plantel con ese identificador." << endl;
									//no se elimina p porque el insertarFinal lo hace en caso de error
									p = nullptr;
								}
							}
							else {
								cout << "Creacion de plantel cancelada." << endl;
								delete p; // eliminar plantel creado
								p = nullptr;
							}
						}
						else if (opcion == lp->getTam() + 2) {
							do {
								do {
									cout << "Elija el plantel a eliminar: " << endl;
									cout << lp->mostrarListaPlanteles(1);
									cin >> opcion;
									system("cls");
								} while (validarEntero(opcion));

								if (opcion == lp->getTam() + 1); // SALIR
								else if (opcion > lp->getTam() + 1 || opcion<1) {
									cout << "Opcion invalida. Intente de nuevo." << endl << endl;
									continue;
								}
								else {
									p = lp->buscarPlantel(opcion);
									if (!p->estaVacio()) {
										cout << "No se puede eliminar el plantel porque aun tiene carros asignados. Operacion cancelada." << endl;
										continue;
									}
									cout << "Esta seguro de eliminar el plantel " << p->getIdentificador() << "? (s/n): ";
									cin >> sn;
									if (sn == 's' || sn == 'S') {
										if (lp->eliminarPlantel(p->getIdentificador())) {
											cout << "Plantel eliminado exitosamente." << endl;
										}
										else {
											cout << "Error: No se pudo eliminar el plantel." << endl;
										}
									}
									else {
										cout << "Eliminacion de plantel cancelada." << endl;
									}
								}
							} while (opcion != lp->getTam() + 1);
						}
						else if (opcion == lp->getTam() + 3) { //modificar precio de categoria especifica de carro (categorias a,b,c,d)
							char categoria;
							double nuevoPrecio;
							do {
								cout << "Digite la categoria de carro a modificar el precio (A, B, C, D): ";
								cin >> categoria;
								categoria = toupper(categoria);
								if(categoria != 'A' && categoria != 'B' && categoria != 'C' && categoria != 'D') {
									cout << "Categoria invalida. Intente de nuevo." << endl;
								}
							} while (categoria != 'A' && categoria != 'B' && categoria != 'C' && categoria != 'D');
							do {
								cout << "Digite el nuevo precio diario para la categoria " << categoria << ": ";
								cin >> nuevoPrecio;
							} while (validarFlotante(nuevoPrecio) || nuevoPrecio < 0);
							if (sucursales->modificarPrecioCategoria(categoria, nuevoPrecio)) {
								cout << "Precio de categoria " << categoria << " modificado exitosamente a " << nuevoPrecio << "." << endl;
							}
							else {
								cout << "Error: No se pudo modificar el precio de la categoria." << endl;
							}

							


							
						}
						else {
							system("cls");
							cout << "Opcion invalida. Intente de nuevo." << endl << endl;
						}

					} while (opcion != lp->getTam() + 4);
					opcion = 0; //reinicia opcion
					break;// Termina gestionar planteles--------------------------------------------------------------------

				case 4:// Inicia gestionar contratos/solicitudes --------------------------------------------------------------------
					do {
						system("cls"); // Limpiar antes de mostrar el menu
						cout << "\n============= GESTION DE TRANSACCIONES ==============\n";
						// Mostrar resumen de Solicitudes y Contratos
						cout << "\n1. Crear Solicitud de Alquiler\n";
						cout << "\n2. Ver Detalle y Gestionar Transaccion (Aprobar/Rechazar/Anular)\n";
						cout << "3. Regresar\n";
						cout << "Seleccione una opcion: ";
						cin >> enteros; // Usar la variable 'enteros' para este submenú

						if (validarEntero(enteros)) continue;

						switch (enteros) {
							case 1: { // Crear Solicitud de Alquiler
								lc = s->getClientes();
								lcol = s->getColaboradores();
								sol = new SolicitudPendiente();
								do {
									cout << "Seleccione el cliente que realiza la solicitud: " << endl;
									cout << s->getClientes()->mostrarPersonas(1);
									cin >> enteros;
									if (validarEntero(enteros)) continue;
								} while (enteros<0 || enteros>lc->getTam() + 1);
								if (enteros == lc->getTam() + 1) {
									delete sol;
									sol = nullptr;
									cout << "Operacion cancelada." << endl;
									break; // cancelar
								}
								cli = dynamic_cast<Cliente*>(lc->obtenerPersonaPorIndice(enteros));
								sol->setCliente(cli);
								do {
									cout << "Seleccione el colaborador que atiende la solicitud: " << endl;
									cout << s->getColaboradores()->mostrarPersonas(1);
									cin >> enteros;
									if (validarEntero(enteros)) continue;
								} while (enteros<0 || enteros>lcol->getTam() + 1);
								if (enteros == lcol->getTam() + 1) {
									delete sol;
									sol = nullptr;
									cout << "Operacion cancelada." << endl;
									break; // cancelar
								}
								colab = dynamic_cast<Colaborador*>(lcol->obtenerPersonaPorIndice(enteros));
								sol->setColaborador(colab);
								do {
									cout << "Seleccione el plantel de donde se alquilara el carro: " << endl;
									cout << s->getPlanteles()->mostrarListaPlanteles(1);
									cin >> enteros;
									if (validarEntero(enteros)) continue;
								} while (enteros<0 || enteros>s->getPlanteles()->getTam() + 1);
								if (enteros == s->getPlanteles()->getTam() + 1) {
									delete sol;
									sol = nullptr;
									cout << "Operacion cancelada." << endl;
									break; // cancelar
								}
								p = s->getPlanteles()->buscarPlantel(enteros);

								// Muetra carros, selecciona por placa y si es invalida repite

								string placaSeleccionada;
								do {
									cout << "Seleccione el carro a alquilar: " << endl;
									cout << p->mostrarEstacionamiento(1);
									cout << "Ingrese la placa del carro: ";
									cin >> placaSeleccionada;
									Carro* carroSeleccionado = p->getCarroxPlaca(placaSeleccionada);
									if (carroSeleccionado && carroSeleccionado->getEstadoCarro() == "Disponible") { // Disponible
										sol->setCarro(carroSeleccionado);
										sol->setPrecioDiario(carroSeleccionado->getPrecioDiario());
										sol->setPrecioTotal(carroSeleccionado->getPrecioDiario());
										// Cambia estado del carro a "Alquilado" HASTA QUE SE APRUEBE LA SOLICITUD
										break; // Carro valido seleccionado
									}
									else {
										cout << "Placa invalida o carro no disponible. Intente de nuevo." << endl;
									}
								} while (true);
								do {
									cout << "Ingrese el numero de dias a alquilar: ";
									cin >> enteros;
								} while (validarEntero(enteros) || enteros < 0);
								sol->setDiasAlquiler(enteros);
								do {
									cout << "Ingrese la fecha de inicio del alquiler (DDMMAAAA): ";
									cin >> enteros;
								} while (validarEntero(enteros) || enteros < 1000000 || enteros > 31129999);
								sol->setFechaInicio(enteros);
								sol->calcularFechaEntrega();

								
								cout << sol->toString() << endl;
								cout << "Esta seguro de crear esta solicitud de alquiler? (s/n): ";
								cin >> sn;
								if (sn == 's' || sn == 'S') {
									if (s->getSolicitudes()->insertarFinal(sol)) {
										cout << "Solicitud de alquiler creada exitosamente." << endl;
										//mandar a historial del cliente una copia de la solicitud
										cli->getHistorial()->insertarFinal(new SolicitudPendiente(*sol));
										//mandar a historial del colaborador una copia de la solicitud
										colab->getHistorial()->insertarFinal(new SolicitudPendiente(*sol));
									}
									else {
										cout << "Error: No se pudo crear la solicitud de alquiler." << endl;
										delete sol;
										sol = nullptr;
									}
								}
								else {
									cout << "Creacion de solicitud de alquiler cancelada." << endl;
									delete sol;
									sol = nullptr;
								}
								break;
							} // <- agregado para evitar caer en case 2
							case 2: { // Ver Detalle y Gestionar Transaccion
								system("cls");
								// Mostrar nuevamente la lista antes de pedir el codigo
								do {
									cout << "1. Ver Solicitudes" << endl;
									cout << "2. Ver Contratos" << endl;
									cout << "3. Regresar" << endl;
									cout << "\nDigite la opcion: ";
									cin >> enteros; // Usar la variable 'textos' para el codigo
									if (!validarEntero(enteros) && enteros < 0 || enteros>3) {
										cout << "Opcion invalida. Intente de nuevo." << endl;
										continue;
									}
								} while (validarEntero(enteros));
								switch (enteros) {
									case 1: {
										lsc = s->getSolicitudes();
										gestionarTransacciones(lsc);
										break;
									}
									case 2: {
										lsc = s->getContratos();
										gestionarTransacciones(lsc);
										break;
									}
									default:
										cout << "Opcion invalida. Intente de nuevo." << endl;
										break;
								}

								break;
							}
							case 3: // Regresar
								//system("cls");
								break;
							default:
								system("cls");
								cout << "Opcion invalida. Intente de nuevo.\n";
								system("pause");
								break;
						}
					} while (enteros != 3);
                    opcion = 0; // Reiniciar 'opcion' para el menu principal
					// Termina gestionar contratos/solicitudes --------------------------------------------------------------------
                }

                // Cierre del switch(opcion) y del bucle interno de la sucursal
            } while (opcion != 5);
            opcion = 0; // Reiniciar opcion para el menu de sucursal
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
			cout << "Opcion invalida. Intente de nuevo." << endl;
		}

	} while (opcion != sucursales->getTam() + 3);
}


