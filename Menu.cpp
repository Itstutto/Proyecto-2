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




void Menu::mostrarTransaccionesColaborador(Sucursal* s, Colaborador* colab) {
	int seleccion = 0;
	ListaSolicitudesContratos* lsc = s->getSolicitudes();
	
	do {
		cout << "\n============= SOLICITUDES PENDIENTES GESTIONADAS POR " << colab->getNombre() << " ==============\n";
		
		// 1. Mostrar la lista filtrada
		cout << colab->mostrarSolicitudesPendientesGestionadas(lsc); 
		cout << "------------------------------------------------------------\n";
		cout << "Seleccione el numero de la solicitud para gestionar o Regresar: ";
		cin >> seleccion;
		system("cls");
		if (validarEntero(seleccion)) continue;
		
		// 2. Obtener la Solicitud seleccionada por el índice FILTRADO
		SolicitudAlquiler* sol = lsc->obtenerTransaccionFiltradaPorIndice(colab->getId(), seleccion);
		
		if (!sol) { // Lógica para salir si se selecciona "Regresar" o es inválido
			int numSolicitudes = 0;
			while (lsc->obtenerTransaccionFiltradaPorIndice(colab->getId(), numSolicitudes + 1)) {
				numSolicitudes++;
			}
			int opcionRegresar = numSolicitudes + 1;
			
			if (seleccion == opcionRegresar) {
				break; // Salir del bucle principal
			}
			
			cout << "Opcion invalida. Intente de nuevo.\n";
			system("cls");
			continue;
		} 
		
		if (sol) {
			// Entrar en el submenú de gestión
			int opcionGestion;
			string textos; // Para el ID del colaborador que aprueba
			
			do {
				
				cout << "\n========= GESTION DE SOLICITUD #" << sol->getCodigoTransaccion() << " =========\n";
				cout << sol->toString();
				cout << "\n----------------------------------------------------\n";
				cout << "1). Aprobar Solicitud (Convertir a Contrato)\n";
				cout << "----------------------------------------------------\n";
				cout << "2). Rechazar Solicitud\n";
				cout << "----------------------------------------------------\n";
				cout << "3). Anular Solicitud\n";
				cout << "----------------------------------------------------\n";
				cout << "4). Regresar\n";
				cout << "----------------------------------------------------\n";
				cout << "Seleccione una opcion: ";
				cin >> opcionGestion;
				system("cls");
				if (validarEntero(opcionGestion)) continue;

				switch (opcionGestion) {
					case 1: { // Aprobar y convertir 
						cout << "\n----------------------------------------------------\n";
						cout << colab->toString() << endl;
						cout << "\n----------------------------------------------------\n";
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
								cout << "Transaccion cancelada, solicitud no dispobinble o carro no disponible" << endl;
							}
						}
						break;
					}
					case 2: { // Rechazar
						system("cls");
						sol->setEstadoTransaccion(3); 
						
						// Actualizar historiales y eliminar de la lista principal
						Cliente* cli = dynamic_cast<Cliente*>(sol->getCliente());
						Colaborador* col = dynamic_cast<Colaborador*>(sol->getColaborador());
						if (cli) cli->getHistorial()->buscarTransaccionPorCodigo(sol->getCodigoTransaccionInt())->setEstadoTransaccion(3);
						if (col) col->getHistorial()->buscarTransaccionPorCodigo(sol->getCodigoTransaccionInt())->setEstadoTransaccion(3);

						lsc->eliminarTransaccionPorCodigo(sol->getCodigoTransaccionInt());
						cout << "------------------------------------------------\n";
						cout << "  SOLICITUD RECHAZADA Y ELIMINADA exitosamente\n";
						cout << "------------------------------------------------\n";
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

								cout << (con->getEstadoDetallado()==2 ? "1). Ejecutar Contrato\n" : "1). Registrar Devolucion y Finalizar Contrato\n" );
								cout << "2). Anular Contrato\n";
								cout << "3). Ver Historial de Carro (Bitacora)\n";
								cout << "4). Regresar\n";
								cout << "\n----------------------------------------------------\n";
								cout << "Seleccione una opcion: ";
								cin >> opcion;
								system("cls");
								if (validarEntero(opcion)) continue;

								switch (opcion) {
									case 1: {
										if (con->getEstadoDetallado() == 2) {
											cout << "Esta seguro que desea ejecutar el contrato? s/n: ";
											cin >> sn;
											if (sn == 's' || sn == 'S') {

												con->setEstadoDetallado(1);
												sucursales->alquilarCarro(alquilados, con->getCarro()->getPlaca());
												con->getCarro()->setEstadosCarro(2, con->getIdColaborador()); // En alquiler
												cout << "Contrato ejecutado" << endl;

												
											}
											else {
												cout << "El contrato NO fue ejecutado" << endl;
											}

											
										}
										else if (con->getEstadoDetallado() == 1) {
											stringstream s;

											cout << "Ingrese la placa del vehiculo: ";
											cin >> textos;
											if (textos != con->getCarro()->getPlaca()) {
												cout << "La placa ingresada no concuerda con la placa del vehiculo ";
											}
											else {
												con->getCarro()->setEstadosCarro(1, con->getIdColaborador());
												con->getCarro()->setEstadosCarro(3, con->getIdColaborador()); // Devuelto
												cout << "Carro devuelto exitosamente al sistema. (Estado: Devuelto)" << endl;
												do {
													cout << "Digite los dias que se utilizo el vehiculo: ";
													cin >> enteros;
													system("cls");
												} while (validarEntero(enteros) || enteros < 0);
												double multa=0;
												double reintegro=0;
												double descuento = 0;
												s << "Precion por Dia: " << con->getPrecioDiario()<<endl;
												s << "SubTotal: " << con->getPrecioTotal()<<endl;
												s << "Dias utilizado: " << enteros << endl;

												if (enteros == con->getDiasAlquiler()) {
													s << "Se entrego el carro a tiempo, no hay multas ni reintegros" << endl;
												}
												else if (enteros > con->getDiasAlquiler()) {
													multa = (enteros - con->getDiasAlquiler()) * (con->getPrecioDiario() * 0.7); // 70% del precio diario por dia extra
													s << "Se entrego el carro con retraso de " << (enteros - con->getDiasAlquiler()) << " dias." << endl;
													s << "Multa aplicada: " << multa << " colones." << endl;
												}
												else {
													reintegro = (con->getDiasAlquiler() - enteros) * (con->getPrecioDiario() * 0.3); // 30% del precio diario por dia anticipado
													s << "Se entrego el carro con anticipacion de " << (con->getDiasAlquiler() - enteros) << " dias." << endl;
													s << "Reintegro aplicado: " << reintegro << " colones." << endl;
												}
												ClienteJuridico* cj = dynamic_cast<ClienteJuridico*>(con->getCliente());
												if (cj) {
													descuento = con->getPrecioTotal()*cj->getPorcentajeDescuento();
													s << "Descuento por cliente juridico " << cj->getPorcentajeDescuento() * 100 << "% :" << descuento;
												}
												s << "Total a pagar: " << con->getPrecioTotal() + multa - reintegro - descuento<<endl;

												do {
													cout << sucursales->mostrarSucursales(2); // No mostrar opcion salir
													cout << "Seleccione la sucursal donde se devuelve el carro: ";
													cin >> enteros;
													if (!sucursales->buscarSucursal(enteros)) {
														cout << "Sucursal no valida. Intente de nuevo." << endl;
													}
												} while (validarEntero(enteros) || !sucursales->buscarSucursal(enteros));
												Sucursal* sucDev = sucursales->buscarSucursal(enteros)->getDato();
												cout << sucDev->getPlanteles()->mostrarListaPlanteles(2); // No mostrar opcion salir
												
												cout << "Seleccione el plantel donde se devuelve el carro: ";
												cin >> enteros;
												int fila, columna;
												bool agregado;
												Plantel* plantelDev = sucDev->getPlanteles()->buscarPlantel(enteros);
												do {
													cout << plantelDev->mostrarEstacionamiento(0) << endl;
													cout << plantelDev->posicionesRecomendadas();
													
													cout << "Digite la fila donde se devolvera el carro: ";
													cin >> fila;
													cout << "Digite la columna donde se devolvera el carro: ";
													cin >> columna;
													
													agregado = plantelDev->agregarCarro(con->getCarro(), fila, columna);
													
													if (!agregado) {
														system("cls");
														cout << "Lugar de estacionamiento no disponible o invalido, intentelo nuevamente" << endl;
													}
													
												}while(!agregado);
												alquilados->desvincularCarro(con->getCarro()->getPlaca());
												s << "Sucursal de devolucion: " << sucDev->getNumeroSucursal() << endl;
												s << "Plantel de devolucion: " << plantelDev->getIdentificador() << endl;
												s << "Ubicacion de devolucion: Fila " << fila << ", Columna " << columna << endl;

												con->setEstadoDetallado(3, s.str());
												cout << "\nContrato finalizado exitosamente.\n"
													<< "Detalle de finalizacion:\n"
													<< con->getEstadoDetalladoStr() << endl;
											}
			
										}
										else {
											cout << "El contrato ya ha sido finalizado previamente.\n";
											
					
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
											con->getCarro()->setEstadosCarro(3, con->getColaborador()->getId());
											cout << "\nCONTRATO ANULADO..\n";
										}
										break;
									}
									case 3: {
										cout << sol->getCarro()->getHistorialEstados();
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
							cout << "Para aprobar una Solicitud debe de hacerse desde el menu del COLABORADOR a cargo" << endl
								<< "En este caso el colaborador " << sol->getColaborador()->getNombre()<<endl;
							system("pause");
							system("cls");
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
							system("cls");
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

void Menu::mostrarReporteContratosPorVehiculo(const string& placa) {
	system("cls");
	cout << sucursales->generarReporteGlobalContratosPorVehiculo(placa) << endl;
	system("pause");
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

	carro4->setEstadosCarro(5, "SISTEMA"); // Revision -> Lavado
	carro4->setEstadosCarro(1, "SISTEMA"); // Lavado -> Disponible
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
	// Solicitud 1: Pendiente (Carro B: 27000 * 5 dias = 135000)
	double pd1 = 27000.00;
	int d1 = 5;
	SolicitudAlquiler* sol1 = new SolicitudPendiente(cf1, co1, carro1, d1, 12062024, 17062024, pd1, pd1 * d1);

	// Solicitud 2: Contrato (Carro C: 45000 * 3 dias = 135000)
	double pd2 = 45000.00;
	int d2 = 3;
	SolicitudAlquiler* sol2 = new SolicitudPendiente(cj1, co2, carro4, d2, 15062024, 18062024, pd2, pd2 * d2); // no se agrega a solicitudes porque se aprueba de una vez
	SolicitudAlquiler* sol3 = new ContratoAlquiler(*sol2); // Contrato basado en la solicitud aprobada

	//primero se hace la solicitud, luego se ingresa en la sucursal y se envia una copia al historial del cliente y el colaborador que aprueba
	suc1->getSolicitudes()->insertarFinal(sol1);
	cf1->getHistorial()->insertarFinal(new SolicitudPendiente(*sol1));
	co1->getHistorial()->insertarFinal(new SolicitudPendiente(*sol1));

	suc1->getSolicitudes()->insertarFinal(sol2);
	cj1->getHistorial()->insertarFinal(new SolicitudPendiente(*sol2));
	co2->getHistorial()->insertarFinal(new SolicitudPendiente(*sol2));


	//para hacer contratos sucursal->convertirSolicitudAContrato(codigo de la transaccion, id colab, solicitudes sucursa, contratos sucursal, clientes sucursal, colaboradores sucursal)
	suc1->convertirSolicitudAContrato(sol2->getCodigoTransaccionInt(), co2->getId(), suc1->getSolicitudes(), suc1->getContratos(), suc1->getClientes(), suc1->getColaboradores());
	

	sucursales->insertarFinal(suc1);


	//Sucursal 2

	Sucursal* suc2 = new Sucursal(2);
	// Crear 3 planteles
	Plantel* plantelB = new Plantel('B', 6, 6);
	Plantel* plantelC = new Plantel('C', 5, 7);
	Plantel* plantelD = new Plantel('D', 8, 5);
	
	// Categorias de los carros: A=Economico, B=Estandar, C= Lujo, D= 4x4
	//crear algunos carros y ponerlos en estado Disponible (Primero se ponen en lavado y despues en disponible)
	Carro* carro7 = new Carro("111-AAA", "Mustang", "Ford", "Lyon", "C1", 'A');
	Carro* carro8 = new Carro("222-BBB", "Camry", "Toyota", "Marseille", "B2", 'B');
	Carro* carro9 = new Carro("333-CCC", "Accord", "Honda", "Nice", "B1", 'B');
	Carro* carro10 = new Carro("444-DDD", "Model 3", "Tesla", "Toulouse", "A1", 'A');
	Carro* carro11 = new Carro("555-EEE", "Ranger", "Ford", "Bordeaux", "C2", 'C');
	Carro* carro12 = new Carro("666-FFF", "Santa Fe", "Hyundai", "Nantes", "B1", 'B');
	//agregar carros categoria C Y D y ponerlos en estado Disponible
	Carro* carro13 = new Carro("777-GGG", "Sprinter", "Mercedes-Benz", "Strasbourg", "1", 'C');
	Carro* carro14 = new Carro("888-HHH", "Defender", "Land Rover", "Lille", "2", 'D');
	// Poner carros en estado Disponible (1) pasando por Lavado (5)


	carro7->setEstadosCarro(5, "SISTEMA"); // Revision -> Lavado
	carro7->setEstadosCarro(1, "SISTEMA"); // Lavado -> Disponible
	carro8->setEstadosCarro(5, "SISTEMA"); // Revision -> Lavado
	carro8->setEstadosCarro(1, "SISTEMA"); // Lavado -> Disponible
	carro9->setEstadosCarro(5, "SISTEMA"); // Revision -> Lavado
	carro9->setEstadosCarro(1, "SISTEMA"); // Lavado -> Disponible
	carro10->setEstadosCarro(5, "SISTEMA"); // Revision -> Lavado
	carro10->setEstadosCarro(1, "SISTEMA"); // Lavado -> Disponible
	carro11->setEstadosCarro(5, "SISTEMA"); // Revision -> Lavado
	carro11->setEstadosCarro(1, "SISTEMA"); // Lavado -> Disponible
	carro12->setEstadosCarro(5, "SISTEMA"); // Revision -> Lavado
	carro12->setEstadosCarro(1, "SISTEMA"); // Lavado -> Disponible
	carro13->setEstadosCarro(5, "SISTEMA"); // Revision -> Lavado
	carro13->setEstadosCarro(1, "SISTEMA"); // Lavado -> Disponible
	carro14->setEstadosCarro(5, "SISTEMA"); // Revision -> Lavado
	carro14->setEstadosCarro(1, "SISTEMA"); // Lavado -> Disponible

	// Agregar carros a los planteles
	plantelB->agregarCarro(carro7, 0, 0);
	plantelB->agregarCarro(carro8, 1, 1);
	plantelC->agregarCarro(carro9, 2, 2);
	plantelC->agregarCarro(carro10, 3, 3);
	plantelD->agregarCarro(carro11, 4, 4);
	plantelD->agregarCarro(carro12, 5, 0);
	plantelD->agregarCarro(carro13, 6, 1);
	plantelD->agregarCarro(carro14, 7, 2);

	// Agregar planteles a la sucursal
	suc2->getPlanteles()->insertarFinal(plantelB);
	suc2->getPlanteles()->insertarFinal(plantelC);
	suc2->getPlanteles()->insertarFinal(plantelD);
	// Agregar algunos clientes (10 clientes : 5 fisicos y 5 juridicos)
	ClienteFisico* cf3 = new ClienteFisico("Luis Martinez", "555", "Francia");
	ClienteJuridico* cj3 = new ClienteJuridico("GlobalTech SARL", "666", "Francia", "Tecnologia", 8.0);
	ClienteFisico* cf4 = new ClienteFisico("Sophie Dubois", "777", "Belgica");
	ClienteJuridico* cj4 = new ClienteJuridico("LogiTrans Ltd.", "888", "Francia", "Logistica", 12.0);
	ClienteFisico* cf5 = new ClienteFisico("Mark Johnson", "999", "Suiza");
	ClienteJuridico* cj5 = new ClienteJuridico("FinanceCorp AG", "1010", "Alemania", "Finanzas", 15.0);
	ClienteFisico* cf6 = new ClienteFisico("Emma Wilson", "1111", "Italia");
	ClienteJuridico* cj6 = new ClienteJuridico("AutoRent SpA", "1212", "Italia", "Alquiler de Vehiculos", 20.0);
	ClienteFisico* cf7 = new ClienteFisico("Oliver Smith", "1313", "España");
	ClienteJuridico* cj7 = new ClienteJuridico("TechLogistics SL", "1414", "España", "Tecnologia y Logistica", 18.0);
	suc2->getClientes()->insertarFinal(cf3);
	suc2->getClientes()->insertarFinal(cj3);
	suc2->getClientes()->insertarFinal(cf4);
	suc2->getClientes()->insertarFinal(cj4);
	suc2->getClientes()->insertarFinal(cf5);
	suc2->getClientes()->insertarFinal(cj5);
	suc2->getClientes()->insertarFinal(cf6);
	suc2->getClientes()->insertarFinal(cj6);
	suc2->getClientes()->insertarFinal(cf7);
	suc2->getClientes()->insertarFinal(cj7);
	// Agregar algunos colaboradores (5 colaboradores)
	Colaborador* co3 = new Colaborador("Isabelle Moreau", "C3", string("10/02/2024"));
	Colaborador* co4 = new Colaborador("Antoine Lefevre", "C4", string("20/03/2023"));
	Colaborador* co5 = new Colaborador("Elena Rossi", "C5", string("05/06/2022"));
	Colaborador* co6 = new Colaborador("Miguel Fernandez", "C6", string("15/09/2021"));
	Colaborador* co7 = new Colaborador("Sofia Garcia", "C7", string("25/12/2020"));
	suc2->getColaboradores()->insertarFinal(co3);
	suc2->getColaboradores()->insertarFinal(co4);
	suc2->getColaboradores()->insertarFinal(co5);
	suc2->getColaboradores()->insertarFinal(co6);
	suc2->getColaboradores()->insertarFinal(co7);


	// Solicitudes y Contratos SUCURSAL 2

	// Solicitud 4: Pendiente (Carro A: 20000 * 4 dias = 80000)
	double pd4 = 20000.00;
	int d4 = 4;
	SolicitudAlquiler* sol4 = new SolicitudPendiente(cf3, co3, carro7, d4, 20062024, 24062024, pd4, pd4 * d4);

	// Solicitud 5: Pendiente (Carro B: 27000 * 2 dias = 54000)
	double pd5 = 27000.00;
	int d5 = 2;
	SolicitudAlquiler* sol5 = new SolicitudPendiente(cj3, co4, carro9, d5, 21062024, 23062024, pd5, pd5 * d5);

	// Solicitud 6: Pendiente (Carro A: 20000 * 6 dias = 120000)
	double pd6 = 20000.00;
	int d6 = 6;
	SolicitudAlquiler* sol6 = new SolicitudPendiente(cf4, co5, carro10, d6, 15062024, 21062024, pd6, pd6 * d6);

	// Solicitud 7: Convertir a Contrato (Carro C: 45000 * 3 dias = 135000)
	double pd7 = 45000.00;
	int d7 = 3;
	SolicitudAlquiler* sol7 = new SolicitudPendiente(cj4, co6, carro11, d7, 18062024, 21062024, pd7, pd7 * d7);


	// Proceso Solicitudes Pendientes
	suc2->getSolicitudes()->insertarFinal(sol4);
	suc2->getSolicitudes()->insertarFinal(sol5);
	suc2->getSolicitudes()->insertarFinal(sol6);
	cf3->getHistorial()->insertarFinal(new SolicitudPendiente(*sol4));
	co3->getHistorial()->insertarFinal(new SolicitudPendiente(*sol4));
	cj3->getHistorial()->insertarFinal(new SolicitudPendiente(*sol5));
	co4->getHistorial()->insertarFinal(new SolicitudPendiente(*sol5));
	cf4->getHistorial()->insertarFinal(new SolicitudPendiente(*sol6));
	co5->getHistorial()->insertarFinal(new SolicitudPendiente(*sol6));

	// Proceso Solicitud 7 (Convertir a Contrato)
	suc2->getSolicitudes()->insertarFinal(sol7);
	cj4->getHistorial()->insertarFinal(new SolicitudPendiente(*sol7));
	co6->getHistorial()->insertarFinal(new SolicitudPendiente(*sol7));
	// Llamada a la funcion de conversion (Elimina sol7 de solicitudes y lo pasa a contratos, actualizando el historial)
	suc2->convertirSolicitudAContrato(sol7->getCodigoTransaccionInt(), co6->getId(), suc2->getSolicitudes(), suc2->getContratos(), suc2->getClientes(), suc2->getColaboradores());
	sucursales->insertarFinal(suc2);

	// --- INICIO DE NUEVO BLOQUE DE DATOS QUEMADOS (SUCURSAL 3) ---

	Sucursal* suc3 = new Sucursal(3);

	// Planteles y Carros para Sucursal 3
	Plantel* plantelE = new Plantel('E', 5, 5); // 25 espacios
	Plantel* plantelF = new Plantel('F', 4, 4); // 16 espacios

	// Carros para Sucursal 3 (Placas 900-XXX a 999-XXX)
	Carro* carro15 = new Carro("900-AAA", "Focus", "Ford", "Bergen", "B1", 'A'); // Se usara en contrato antiguo (2023)
	Carro* carro16 = new Carro("911-BBB", "Escape", "Ford", "Oslo", "C1", 'B'); // Se usara en contrato reciente (2025)
	Carro* carro17 = new Carro("922-CCC", "Prius", "Toyota", "Trondheim", "A1", 'A'); // Disponible
	Carro* carro18 = new Carro("933-DDD", "Pilot", "Honda", "Stavanger", "C2", 'C'); // Contrato Alquilado (estado 2)
	Carro* carro19 = new Carro("944-EEE", "Range Rover", "Land Rover", "Oslo", "D2", 'D'); // Disponible

	// Poner carros en estado Disponible (1) pasando por Lavado (5)
	carro15->setEstadosCarro(5, "SISTEMA");
	carro15->setEstadosCarro(1, "SISTEMA");
	carro16->setEstadosCarro(5, "SISTEMA");
	carro16->setEstadosCarro(1, "SISTEMA");
	carro17->setEstadosCarro(5, "SISTEMA");
	carro17->setEstadosCarro(1, "SISTEMA");
	carro19->setEstadosCarro(5, "SISTEMA");
	carro19->setEstadosCarro(1, "SISTEMA");

	// Carro 18 se deja en estado Alquilado (2)
	carro18->setEstadosCarro(5, "SISTEMA");
	carro18->setEstadosCarro(1, "SISTEMA");
	carro18->setEstadosCarro(2, "C8"); // Disponible -> Alquilado

	// Agregar carros a planteles
	plantelE->agregarCarro(carro15, 0, 0);
	plantelE->agregarCarro(carro16, 1, 1);
	plantelE->agregarCarro(carro17, 2, 2);
	plantelF->agregarCarro(carro18, 0, 0); // Ocupa espacio
	plantelF->agregarCarro(carro19, 1, 1);

	// Agregar planteles a la sucursal
	suc3->getPlanteles()->insertarFinal(plantelE);
	suc3->getPlanteles()->insertarFinal(plantelF);

	// Clientes
	ClienteFisico* cf8 = new ClienteFisico("Peter Hansen", "1515", "Noruega");
	ClienteJuridico* cj8 = new ClienteJuridico("Norway Rent A Car", "1616", "Noruega", "Alquiler", 10.0);
	ClienteFisico* cf9 = new ClienteFisico("Eva Jensen", "1717", "Dinamarca");

	suc3->getClientes()->insertarFinal(cf8);
	suc3->getClientes()->insertarFinal(cj8);
	suc3->getClientes()->insertarFinal(cf9);

	// Colaboradores
	Colaborador* co8 = new Colaborador("Nils Olsen", "C8", string("01/01/2023")); // Sera el colaborador con mas contratos
	Colaborador* co9 = new Colaborador("Lars Pedersen", "C9", string("10/11/2024"));

	suc3->getColaboradores()->insertarFinal(co8);
	suc3->getColaboradores()->insertarFinal(co9);


	// Solicitudes y Contratos SUCURSAL 3

	// Solicitud 8: Convertir a Contrato (Carro A: 20000 * 7 dias = 140000). Contrato Antiguo (05/11/2023)
	double pd8 = 20000.00;
	int d8 = 7;
	SolicitudAlquiler* sol8_base = new SolicitudPendiente(cf8, co8, carro15, d8, 05112023, 12112023, pd8, pd8 * d8);

	// Solicitud 9: Convertir a Contrato (Carro C: 45000 * 5 dias = 225000). Contrato Alquilado (28/10/2025)
	double pd9 = 45000.00;
	int d9 = 5;
	SolicitudAlquiler* sol9_base = new SolicitudPendiente(cj8, co8, carro19, d9, 28102025, 02112025, pd9, pd9 * d9);

	// Solicitud 10: Convertir a Contrato (Carro B: 27000 * 10 dias = 270000). Contrato Reciente (30/10/2025)
	double pd10 = 27000.00;
	int d10 = 10;
	SolicitudAlquiler* sol10_base = new SolicitudPendiente(cf9, co9, carro16, d10, 30102025, 9112025, pd10, pd10 * d10);

	// Proceso Solicitudes a Contrato (Se repite el patron de SUCURSAL 1)

	// Solicitud 8
	suc3->getSolicitudes()->insertarFinal(sol8_base);
	cf8->getHistorial()->insertarFinal(new SolicitudPendiente(*sol8_base));
	co8->getHistorial()->insertarFinal(new SolicitudPendiente(*sol8_base));
	suc3->convertirSolicitudAContrato(sol8_base->getCodigoTransaccionInt(), co8->getId(), suc3->getSolicitudes(), suc3->getContratos(), suc3->getClientes(), suc3->getColaboradores());

	// Solicitud 9
	suc3->getSolicitudes()->insertarFinal(sol9_base);
	cj8->getHistorial()->insertarFinal(new SolicitudPendiente(*sol9_base));
	co8->getHistorial()->insertarFinal(new SolicitudPendiente(*sol9_base));
	suc3->convertirSolicitudAContrato(sol9_base->getCodigoTransaccionInt(), co8->getId(), suc3->getSolicitudes(), suc3->getContratos(), suc3->getClientes(), suc3->getColaboradores());

	// Solicitud 10
	suc3->getSolicitudes()->insertarFinal(sol10_base);
	cf9->getHistorial()->insertarFinal(new SolicitudPendiente(*sol10_base));
	co9->getHistorial()->insertarFinal(new SolicitudPendiente(*sol10_base));
	suc3->convertirSolicitudAContrato(sol10_base->getCodigoTransaccionInt(), co9->getId(), suc3->getSolicitudes(), suc3->getContratos(), suc3->getClientes(), suc3->getColaboradores());

	sucursales->insertarFinal(suc3);

	// --- FIN DE NUEVO BLOQUE DE DATOS QUEMADOS (SUCURSAL 3) ---


}
void Menu::iniciar() {
	inicializarDatos();
	menuPrincipal();
}

void Menu::menuPrincipal() {
	system("cls");
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
								cout << "\nCliente: " << cli->getNombre() << " (ID: " << cli->getId() << ")\n";
								cout << "----------------------------------------------------\n";
								// Usar el método actualizado de Cliente:
								cout << cli->mostrarCliente(); // Ahora muestra 1-4 y 5. Regresar
								
								cout << "Seleccione una opcion: ";
								cin >> opcion;
								system("cls");
								if (validarEntero(opcion)) continue; // Volver al inicio del do-while si es inválido
														
								switch (opcion) {
								case 1: { // Modificar informacion del cliente-----------------------------------------------------------------------------
									
									bool tipoCliente = dynamic_cast<ClienteFisico*>(cli) != nullptr; // true si es ClienteFisico, false si es ClienteJuridico
									int limite = tipoCliente ? 4 : 6; // Numero de opciones segun el tipo de cliente
									int opcionModificar;
									do {
										do {
											
											cout << cli->mostrarModificar() << endl;
											cout << "Seleccione la opcion a modificar (o " << limite << " para regresar): ";
											cin >> opcionModificar;
											system("cls");
										} while (validarEntero(opcionModificar));

										if (opcionModificar > limite) {
											system("cls");
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
									system("cls");
									cout << "Informacion del Cliente:" << endl;
									cout << cli->toString() << endl;
									system("pause");
									break;
								case 3:
									system("cls");
									cout << cli->getHistorial()->mostrarHistorialCompletado() << endl;
									system("pause");
									break;
								case 4: // NUEVA OPCION: Ver Solicitudes Pendientes
									system("cls");
									mostrarTransaccionesCliente(s, cli);
									break;
								case 5: // Regresar (Opción anterior era 4)
									break;
								default:
									system("cls");
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
								cout << "Elija el tipo de cliente a agregar: " << endl
									<< "-------------------------------------------" << endl
									<< "1). Cliente Fisico" << endl
									<< "-------------------------------------------" << endl
									<< "2). Cliente Juridico" << endl
									<< "-------------------------------------------" << endl
									<< "seleccione una opcion: ";
								cin >> tipoCliente;
								if (!validarEntero(tipoCliente) && (tipoCliente != 1 && tipoCliente != 2)) {
									cout << "Opcion invalida. Intente de nuevo." << endl;
									system("pause");
									system("cls");
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
								system("pause");	
								system("cls");
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
							system("cls");
							if (sn == 's' || sn == 'S') {
								if (lc->insertarFinal(cli)) {
									cout << "Cliente agregado exitosamente." << endl;
									system("pause");
									system("cls");
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
										system("pause");
										system("cls");
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
											system("pause");
											system("cls");

										}
										else {
											cout << "Error: No se pudo eliminar el cliente." << endl;
											system("pause");
											system("cls");
										}
									}
									else {
										cout << "Eliminacion de cliente cancelada." << endl;
										system("pause");
										system("cls");
									}
								}
								else {
									system("cls");
									cout << "Opcion invalida. Intente de nuevo." << endl << endl;
									system("pause");
									system("cls");
								}

							} while (opcion != lc->getTam() + 1);

						}
						else if (opcion == lc->getTam() + 4); // Salir
                        
                        // Manejo de opción inválida
                        else {
                            system("cls");
                            cout << "Opcion invalida. Intente de nuevo." << endl << endl;
							system("pause");
							system("cls");
                        }
					} while (opcion != lc->getTam() + 4);
					opcion = 0; // Reiniciar opcion para el menu de sucursal
                        break; // Termina gestionar clientes--------------------------------------------------------------------

                case 2:// Inicia gestionar colaboradores--------------------------------------------------------------------
					lcol = s->getColaboradores();
					do {
						system("cls");
						do {
							cout << s->getColaboradores()->mostrarPersonas(0);
							cin >> opcion;
							system("cls");
						} while (validarEntero(opcion));
						if (opcion >= 1 && opcion <= lcol->getTam()) {
							// Inicia Mostrar detalles del colaborador seleccionado-----------------------------------------------------------------------------
							colab = dynamic_cast<Colaborador*>(lcol->obtenerPersonaPorIndice(opcion));
							
							do { // Submenu de Detalle de Colaborador 
								
								cout << "\nColaborador: " << colab->getNombre() << " (ID: " << colab->getId() << ")\n";
								cout << "----------------------------------------------------\n";
								cout << "1). Ver Informacion Detallada\n";
								cout << "----------------------------------------------------\n";
								cout << "2). Ver Solicitudes Pendientes Gestionadas\n";
								cout << "----------------------------------------------------\n";
								cout << "3). Reporte Contratos Realizados\n"; 
								cout << "----------------------------------------------------\n";
								cout << "4). Regresar\n";
								cout << "----------------------------------------------------\n";
								cout << "Seleccione una opcion: ";
								cin >> enteros; 
								if (validarEntero(enteros)) continue;
								system("cls");
								switch (enteros) {
								case 1: // VER INFORMACION DETALLADA DEL COLABORADOR
									system("cls");
									cout << "Informacion del Colaborador:" << endl;
									cout << colab->toString() << endl;
									system("pause");
									break;
								case 2: // GESTION DE SOLICITUDES DEL COLABORADOR
									mostrarTransaccionesColaborador(s, colab);
									break;
								case 3: // REPORTE DE CONTRATOS REALIZADOS POR EL COLABORADOR
									cout << colab->generarReporteContratosRealizados() << endl;
									system("pause");
									break;
								case 4: // Regresar
									break;
								default:
									cout << "Opcion invalida.\n";
									system("pause");
									break;
								}

							} while (enteros != 4);
							opcion = 0; // reinicia para el menu
							
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
						else if (opcion == lcol->getTam() + 3) system("cls"); // Salir
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
						system("cls");
						do {
							cout << lp->mostrarListaPlanteles(0);
							cin >> opcion;
							system("cls");
						} while (validarEntero(opcion));
						if (opcion == lp->getTam() + 5); // Salir
						else if (opcion >= 1 && opcion <= lp->getTam()) {
							// Inicia Mostrar detalles del plantel seleccionado-----------------------------------------------------------------------------

							p = lp->buscarPlantel(opcion);
							do {
								do {
									cout << p->mostrarPlantel();
									cin >> opcion;
									system("cls");
								} while (validarEntero(opcion));
								switch (opcion) {
								case 1: // Ver todos los carros
									cout << p->mostrarEstacionamiento(0)<<endl;
									system("pause");
									system("cls");
									break;
								case 2: {// Ver carro especifico
									do {
										if (p->getCanTotal() == p->getCanDisponibles()) {
											cout << "No hay ningun carro en el plantel" << endl;
											system("pause");
											system("cls");
											car = nullptr;
										
											break;
										}
										cout << p->mostrarEstacionamiento(0);
										cout << "Digite la placa del carro a ver: ";
										cin >> textos;
										car = p->getCarroxPlaca(textos);
										system("cls");
										if (!car) cout << "No se encontro un carro con esa placa. Intente de nuevo." << endl;
									} while (!car);
									if (!car) break;
									do {
										do {
											cout << car->mostrarCarro();
											cin >> opcion;
											system("cls");
										} while (validarEntero(opcion));
										switch (opcion) {
										case 1: // Ver informacion detallada del carro
											cout << car->toString();
											break;
										case 2: // Cambiar estado del carro
											cout << "Estado actual del carro: " << car->getEstadoCarro() << endl;

											do {
												cout << s->getColaboradores()->mostrarPersonas(1);
												cout << "Seleccione el colaborador que realiza el cambio de estado: ";
												cin >> enteros;
												system("cls");
											} while (validarEntero(enteros));
											if (s->getColaboradores()->getTam() + 1 == enteros) break; // Regresar
											if (!s->getColaboradores()->obtenerPersonaPorIndice(enteros)) {
												cout << "Opcion invalida. Intente de nuevo." << endl;
												continue;
											}
											colab = dynamic_cast<Colaborador*>(s->getColaboradores()->obtenerPersonaPorIndice(enteros));

											do {
												cout << car->mostrarEstadosCarro();
												cout << "Digite el nuevo estado para el carro: ";
												cin >> enteros;
											} while (validarEntero(enteros));
											int resultado;
											switch (enteros) {
											case 1: // Disponible
												resultado = car->setEstadosCarro(enteros, colab->getId());
												break;
											case 2: // Alquilado
												resultado = car->setEstadosCarro(4, colab->getId());
												break;
											case 3: // En Mantenimiento
												resultado = car->setEstadosCarro(5, colab->getId());
												break;
											}
											if (resultado == 1) { 
												cout << "Estado del carro actualizado exitosamente." << endl;
												system("pause");
											}
											else if (resultado == -2) {
												cout << "Error: El carro ya se encuentra en ese estado." << endl;
												system("pause");
											}
											else if (resultado == -1) {
												cout << "Error: No se puede cambiar al estado desde el estado actual." << endl;
												system("pause");
											}
											else {
												cout << "Error: No se pudo actualizar el estado del carro." << endl;
												system("pause");
											}
										case 3: { // Mover carro a otro plantel
											if (car->getEstadoCarro() == "Alquilado") {
												cout << "No se puede mover el carro porque esta alquilado. Operacion cancelada." << endl;
												break;
											}
											do {
												cout << sucursales->mostrarSucursales(1);
												cout << "Seleccione la sucursal destino: ";
												cin >> enteros;
												system("cls");
											} while (validarEntero(enteros));
											if (enteros == sucursales->getTam() + 1) break; // Regresar
											Sucursal* sucDestino = sucursales->obtenerSucursalPorIndice(enteros);
											if (!sucDestino) {
												cout << "Opcion invalida. Intente de nuevo." << endl;
												break;
											}

											do {
												cout << sucDestino->getPlanteles()->mostrarListaPlanteles(1);
												cout << "Seleccione el plantel destino: ";
												cin >> enteros;
												system("cls");
											} while (validarEntero(enteros));
											if (enteros == sucDestino->getPlanteles()->getTam() + 1) break; // Regresar
											Plantel* plantelDestino = sucDestino->getPlanteles()->buscarPlantel(enteros);
											if (!plantelDestino) {
												cout << "Opcion invalida. Intente de nuevo." << endl;
												break;
											}
											int fila, columna;
											do {
												cout << plantelDestino->mostrarEstacionamiento(1);
												cout << plantelDestino->posicionesRecomendadas() << endl;
												do {
													cout << "Digite la fila donde desea mover el carro: ";
													cin >> fila;
												} while (validarEntero(fila));
												do {
													cout << "Digite la columna donde desea mover el carro: ";
													cin >> columna;
												} while (validarEntero(columna));
												if (!plantelDestino->esPosicionValida(fila, columna)) {
													system("cls");
													cout << "Posicion invalida o ya ocupada. Intente de nuevo." << endl;
												}
											} while (!plantelDestino->esPosicionValida(fila, columna));
											if (p->moverCarro(car->getPlaca(), plantelDestino, fila, columna)) {
												cout << "Carro movido exitosamente al plantel " << plantelDestino->getIdentificador() << " de la sucursal " << sucDestino->getNumeroSucursal() << "." << endl;
											}
											else {
												cout << "Error: No se pudo mover el carro." << endl;
											}

										}
										case 4: { // Reporte de contratos para vehiculo especifico (10 pts)
											mostrarReporteContratosPorVehiculo(car->getPlaca());
											break;
										}
										case 5: // Regresar
											system("cls");
											break; 
										default:
											cout << "Opcion invalida. Intente de nuevo." << endl;
											system("cls");
											break;
										}

									} while (opcion != 5); // Regresar
									system("pause");
									break;
								}
								case 3: // Agregar nuevo carro
									
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
									do {
										cout << "Digite la categoria del carro (A, B, C, D): ";
										cin >> carac;
										if (carac != 'A' && carac != 'B' && carac != 'C' && carac != 'D') {
											system("cls");
											cout << "Elija una categoria valida" << endl
												<< "-----------------------------------------------------------------"<<endl;
										}
									} while (carac != 'A' && carac != 'B' && carac != 'C' && carac != 'D');
									car->setCategoria(carac);
									int fila, columna;
									do {
										
										do {
											system("cls");
											cout << p->mostrarEstacionamiento(0);
											cout << "Digite la posicion donde desea agregar el carro " << endl;
											cout << "Ubicaciones recomendadas: " << p->posicionesRecomendadas() << endl;
											cout << "Fila: ";
											cin >> fila;

										} while (validarEntero(fila));
										
										do {
											system("cls");
											cout << p->mostrarEstacionamiento(0);
											cout << "Columna: ";
											cin >> columna;
										} while (validarEntero(columna));

										if (!p->esPosicionValida(fila, columna)) {
											system("cls");
											cout << "Posicion invalida o ya ocupada. Intente de nuevo." << endl;
											system("pause");
											system("cls");
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
											system("pause");
											system("cls");
										}
										else {
											cout << "Error: No se pudo agregar el carro. Puede que ya exista un carro con esa placa." << endl;
											system("pause");
											system("cls");
											//no se elimina car porque el agregarCarro lo hace en caso de error
											car = nullptr;
										}
									}
									else {
										cout << "Creacion de carro cancelada." << endl;
										system("pause");
										system("cls");
										delete car; // eliminar carro creado
										car = nullptr;
									}
									break;
								case 4: // Eliminar carro
									do {
										cout << p->mostrarEstacionamiento(0);
										cout << "Digite la placa del carro a eliminar: ";
										cin >> textos;
										car = p->getCarroxPlaca(textos);
									} while (!car);
									if(car->getEstadoCarro() == "Alquilado") {
										cout << "No se puede eliminar el carro porque esta alquilado. Operacion cancelada." << endl;
										system("pause");
										system("cls");
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
											system("pause");
											system("cls");
										}
										else {
											cout << "Error: No se pudo eliminar el carro." << endl;
											system("pause");
											system("cls");
										}
									}
									else {
										cout << "Eliminacion de carro cancelada." << endl;
										system("pause");
										system("cls");
									}
								case 5: 
									break; // Regresar
								default:
									cout << "Opcion invalida. Intente de nuevo." << endl;
									system("pause");
									system("cls");
									break;
								}
							} while (opcion != 5);
							opcion = 0; // Reiniciar opcion para el menu de planteles
						}
						else if (opcion == lp->getTam() + 1) { // Agregar nuevo plantel
							p = new Plantel();
							cout << "Digite el identificador del plantel (A-Z): ";
							cin >> carac;
							if (lp->buscarPlantel(carac)) {
								cout << "Plantel con ese identificador ya existe. Operacion cancelada." << endl;
								system("pause");
								system("cls");
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
									system("pause");
									system("cls");
								}
								else {
									cout << "Error: No se pudo agregar el plantel. Puede que ya exista un plantel con ese identificador." << endl;
									system("pause");
									system("cls");
									//no se elimina p porque el insertarFinal lo hace en caso de error
									p = nullptr;
								}
							}
							else {
								cout << "Creacion de plantel cancelada." << endl;
								system("pause");
								system("cls");
								delete p; // eliminar plantel creado
								p = nullptr;
							}
						}
						else if (opcion == lp->getTam() + 2) { // Eliminar plantel
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
								cout << "Digite la categoria de carro a modificar el precio (A, B, C, D) o digite 'X' para cancelar: ";
								cin >> categoria;
								categoria = toupper(categoria);
								if(categoria != 'A' && categoria != 'B' && categoria != 'C' && categoria != 'D' && categoria != 'X') {
									cout << "Categoria invalida. Intente de nuevo." << endl;
									system("cls");
								}
							} while (categoria != 'A' && categoria != 'B' && categoria != 'C' && categoria != 'D' && categoria != 'X');
							if (categoria == 'X') {
								cout << "Operacion cancelada." << endl;
								system("cls");
								continue;
							} 
							do {
								cout << "Digite el nuevo precio diario para la categoria " << categoria << ": ";
								cin >> nuevoPrecio;
							} while (validarFlotante(nuevoPrecio) || nuevoPrecio < 0);
							if (sucursales->modificarPrecioCategoria(categoria, nuevoPrecio)) {
								cout << "Precio de categoria " << categoria << " modificado exitosamente a " << nuevoPrecio << "." << endl;
								system("cls");
							}
							else {
								cout << "Error: No se pudo modificar el precio de la categoria." << endl;
								system("cls");
							}

							
						}
						else if (opcion == lp->getTam() + 4) { // NUEVO: Reporte de Ocupacion de Planteles
							system("cls");
							cout << s->generarReporteOcupacionPlanteles() << endl;
							system("pause");
						}
						else { // Manejo de opcion invalida
							system("cls");
							cout << "Opcion invalida. Intente de nuevo." << endl << endl;
						}

					} while (opcion != lp->getTam() + 5);
					opcion = 0; //reinicia opcion
					break;// Termina gestionar planteles--------------------------------------------------------------------

				case 4:// Inicia gestionar contratos/solicitudes --------------------------------------------------------------------
					do {
						system("cls"); // Limpiar antes de mostrar el menu
						cout << "\n=================== GESTION DE TRANSACCIONES ====================\n";
						// Mostrar resumen de Solicitudes y Contratos
						cout << "-----------------------------------------------------------------\n";
						cout << "1). Crear Solicitud de Alquiler\n";
						cout << "-----------------------------------------------------------------\n";
						cout << "2). Ver Detalle y Gestionar Transaccion (Aprobar/Rechazar/Anular)\n";
						cout << "-----------------------------------------------------------------\n";
						cout << "3). Regresar\n";
						cout << "-----------------------------------------------------------------\n";
						cout << "Seleccione una opcion: ";
						cin >> enteros; // Usar la variable 'enteros' para este submenú

						if (validarEntero(enteros)) continue;

						switch (enteros) {
							case 1: { // Crear Solicitud de Alquiler
								system("cls");	
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
									system("cls");
									cout << "Operacion cancelada." << endl;
									system("pause");
									system("cls");
									break; // cancelar
								}
								cli = dynamic_cast<Cliente*>(lc->obtenerPersonaPorIndice(enteros));
								sol->setCliente(cli);
								do {
									system("cls");
									cout << "Seleccione el colaborador que atiende la solicitud: " << endl;
									cout << s->getColaboradores()->mostrarPersonas(1);
									cin >> enteros;
									if (validarEntero(enteros)) continue;
								} while (enteros<0 || enteros>lcol->getTam() + 1);
								if (enteros == lcol->getTam() + 1) {
									delete sol;
									sol = nullptr;
									system("cls");
									cout << "Operacion cancelada." << endl;
									system("pause");
									system("cls");
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
									system("cls");
									cout << "Operacion cancelada." << endl;
									system("pause");
									system("cls");
									break; // cancelar
								}
								p = s->getPlanteles()->buscarPlantel(enteros);

								if (p->getCanCarrosDisponibles() == 0) {
									system("cls");
									cout << "No hay carros disponibles en el plantel seleccionado"<<endl
										<<"Operacion cancelada" << endl;
									system("pause");
									system("cls");
									delete sol;
									sol = nullptr;
									break;
								}

								// Muetra carros, selecciona por placa y si es invalida repite
								Carro* carroSeleccionado;
								string placaSeleccionada;
								do {
									cout << "Seleccione el carro a alquilar: " << endl;
									cout << p->mostrarEstacionamiento(1);
									cout << "Ingrese la placa del carro: ";
									cin >> placaSeleccionada;
									carroSeleccionado = p->getCarroxPlaca(placaSeleccionada);
									if (carroSeleccionado && carroSeleccionado->getEstadoCarro() == "Disponible") { // Disponible
										sol->setCarro(carroSeleccionado);
										
										// Cambia estado del carro a "Alquilado" HASTA QUE SE APRUEBE LA SOLICITUD
										break; // Carro valido seleccionado
									}
									else {
										system("cls");
										cout << "Placa invalida o carro no disponible. Intente de nuevo." << endl;
										system("pause");
										system("cls");
									}
								} while (true);
								do {
									cout << "Ingrese el numero de dias a alquilar: ";
									cin >> enteros;
								} while (validarEntero(enteros) || enteros < 0);
								sol->setDiasAlquiler(enteros);
								sol->setPrecioDiario(carroSeleccionado->getPrecioDiario());
								sol->setPrecioTotal(carroSeleccionado->getPrecioDiario());
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
										system("cls");
										cout << "Solicitud de alquiler creada exitosamente." << endl;
										system("pause");
										system("cls");
										//mandar a historial del cliente una copia de la solicitud
										cli->getHistorial()->insertarFinal(new SolicitudPendiente(*sol));
										//mandar a historial del colaborador una copia de la solicitud
										colab->getHistorial()->insertarFinal(new SolicitudPendiente(*sol));
									}
									else {
										system("cls");
										cout << "Error: No se pudo crear la solicitud de alquiler." << endl;
										system("pause");
										system("cls");
										delete sol;
										sol = nullptr;
									}
								}
								else {
									system("cls");
									cout << "Creacion de solicitud de alquiler cancelada." << endl;
									system("pause");
									system("cls");
									delete sol;
									sol = nullptr;
								}
								break;
							} 
							case 2: { // Ver Detalle y Gestionar Transaccion
								system("cls");
								// Mostrar nuevamente la lista antes de pedir el codigo
								do {
									cout << "=======Ver Detalle y Gestionar Transaccion=======" << endl;
									cout << "-------------------------------------------------\n";
									cout << "1). Ver Solicitudes" << endl;
									cout << "-------------------------------------------------\n";
									cout << "2). Ver Contratos" << endl;
									cout << "-------------------------------------------------\n";
									cout << "3). Regresar" << endl;
									cout << "-------------------------------------------------\n";
									cout << "Seleccione una opcion: ";
									cin >> enteros; // Usar la variable 'textos' para el codigo
									if (!validarEntero(enteros) && enteros < 0 || enteros>3) {
										cout << "Opcion invalida. Intente de nuevo." << endl;
										continue;
									}
									if (validarEntero(enteros)) continue;
								
									switch (enteros) {
										case 1: { // Ver Solicitudes
											system("cls");
											lsc = s->getSolicitudes();
											gestionarTransacciones(lsc);
											system("cls");
											continue;
										}
										case 2: { // Ver Contratos
											system("cls");
											lsc = s->getContratos();
											gestionarTransacciones(lsc);
											system("cls");
											continue;
										}
										case 3: // Regresar
										system("cls");
										break;
										default:
											system("cls");
											cout << "Opcion invalida. Intente de nuevo." << endl;
											system("pause");
											continue;
									}
									
								} while (enteros != 3);
								enteros = 0; // Reiniciar 'enteros' para el menu de gestionar transacciones
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
						system("cls");
						cout << "Sucursal creada exitosamente." << endl;
						system("pause");
						system("cls");
					}
					else {
						system("cls");	
						cout << "Error: No se pudo crear la sucursal. Puede que ya exista una sucursal con ese numero." << endl;
						system("pause");
						system("cls");
						delete nuevaSuc;
						nuevaSuc = nullptr;
					}
				}
				else {
					system("cls");
					cout << "Creacion de sucursal cancelada." << endl;
					system("pause");
					system("cls");
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
					system("pause");
					system("cls");
					continue; // reintentar si esta fuera de rango
				}
				break; // valido
			}

			if (!cancelar) {
				Sucursal* sel = sucursales->obtenerSucursalPorIndice(enteros);
				if (!sel) {
					system("cls");
					cout << "Seleccion invalida. Intente de nuevo." << endl;
					system("pause");
					system("cls");
				}
				else {
					cout << "Esta seguro de eliminar la sucursal numero " << sel->getNumeroSucursal() << "? \nCon esto elimina TODO (Planteles, Carros, Contratos, CLientes, etc) (s/n): ";
					cin >> sn;
					if (sn == 's' || sn == 'S') {
						if (sucursales->eliminarSucursal(sel->getNumeroSucursal())) {
							system("cls");
							cout << "Sucursal eliminada exitosamente." << endl;
							system("pause");
							system("cls");
							opcion = 0;
						}
						else {
							system("cls");	
							cout << "Error: No se pudo eliminar la sucursal." << endl;
							system("pause");
							system("cls");
						}
					}
					else {
						system("cls");
						cout << "Eliminacion de sucursal cancelada." << endl;
						system("pause");
						system("cls");
					}
				}
				system("pause");
				system("cls");
			}
			// si cancelar==true, simplemente volver al menu principal
		}//Termina eliminar sucursal--------------------------------------------------------------------
		else {
			cout << "Opcion invalida. Intente de nuevo." << endl;
		}

	} while (opcion != sucursales->getTam() + 3);
}


