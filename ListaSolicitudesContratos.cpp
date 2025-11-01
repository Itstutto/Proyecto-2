#include "ListaSolicitudesContratos.h"
#include "ContratoAlquiler.h"
#include <ctime>

ListaSolicitudesContratos::ListaSolicitudesContratos() : primero(nullptr), ultimo(nullptr), tam(0) {}

ListaSolicitudesContratos::~ListaSolicitudesContratos() {
	NodoSolicitud* a = primero;
	while (a) {
		NodoSolicitud* s = a->getSig();
		delete a->getDato();
		delete a;
		a = s;
	}
}
int ListaSolicitudesContratos::getTam() const {
	return tam;
}

bool ListaSolicitudesContratos::insertarFinal(SolicitudAlquiler* s) {
	if (!s) return false;
	NodoSolicitud* n = new NodoSolicitud(s);
	if (!primero) {
		primero = ultimo = n;
	} else {
		ultimo->setSig(n);
		ultimo = n;
	}
	tam++;
	return true;
}

SolicitudAlquiler* ListaSolicitudesContratos::buscarTransaccion(const int& pos) {
	if (pos < 1 || pos > tam) return nullptr;
	NodoSolicitud* a = primero;
	int contador = 1;
	while (a) {
		if (contador == pos) {
			return a->getDato();
		}
		a = a->getSig();
		contador++;
	}
	return nullptr;
}
SolicitudAlquiler* ListaSolicitudesContratos::buscarTransaccionPorCodigo(const int& codigo) {
	NodoSolicitud* a = primero;
	while (a) {
		if (a->getDato()->getCodigoTransaccionInt() == codigo) {
			return a->getDato();
		}
		a = a->getSig();
	}
	return nullptr;
}

bool ListaSolicitudesContratos::transaccionesCliente(string id)
{
	NodoSolicitud* a = primero;
	while (a) {
		if (a->getDato()->getIdCliente() == id) {
			return true;
		}
		a = a->getSig();
	}
	return false;
}

bool ListaSolicitudesContratos::transaccionesColaborador(string id)
{
	NodoSolicitud* a = primero;
	while (a) {
		if (a->getDato()->getIdColaborador() == id) {
			return true;
		}
		a = a->getSig();
	}
	return false;
}

void ListaSolicitudesContratos::clienteEliminado(string id)
{
	// Se crea solo cliente fisico porque nada mas es para identificacion, no importa el tipo
	NodoSolicitud* a = primero;
	while (a) {
		if (a->getDato()->getIdCliente() == id) {
			Cliente* c = new ClienteFisico(a->getDato()->getCliente()->getNombre()+" ELIMINADO", a->getDato()->getIdCliente() + " ELIMINADO", "N/A");
			a->getDato()->setCliente(nullptr); // Desvincula el cliente eliminado
			a->getDato()->setCliente(c); // Asigna un cliente por defecto
		}
		a = a->getSig();
	}
}

void ListaSolicitudesContratos::colaboradorEliminado(string id)
{
	NodoSolicitud* a = primero;
	while (a) {
		if (a->getDato()->getIdColaborador() == id) {
			Colaborador* c = new Colaborador("Colaborador ELIMINADO", id + " ELIMINADO", 0);
			a->getDato()->setColaborador(nullptr); // Desvincula el colaborador eliminado
			a->getDato()->setColaborador(c); // Asigna un colaborador por defecto
		}
		a = a->getSig();
	}
}
void ListaSolicitudesContratos::vehiculoEliminado(string placa)
{
	NodoSolicitud* a = primero;
	while (a) {
		if (a->getDato()->getPlacaVehiculo() == placa) {
			Carro* temp = a->getDato()->getCarro();
			Carro* c = new Carro(temp->getPlaca() + " ELIMINADO", temp->getModelo() + " ELIMINADO",temp->getMarca()+" ELIMINADO", "Basurero", "N/A", '0');
			a->getDato()->setCarro(nullptr); // Desvincula el vehiculo eliminado
			a->getDato()->setCarro(c); // Asigna un vehiculo por defecto
		}
		a = a->getSig();
	}
}

void ListaSolicitudesContratos::eliminarTransaccionPorCodigo(const int& codigo)
{
	NodoSolicitud* a = primero;
	NodoSolicitud* anterior = nullptr;
	while (a) {
		if (a->getDato()->getCodigoTransaccionInt() == codigo) {
			if (anterior) {
				anterior->setSig(a->getSig());
			} else {
				primero = a->getSig();
			}
			if (a == ultimo) {
				ultimo = anterior;
			}
			delete a->getDato();
			delete a;
			tam--;
			return;
		}
		anterior = a;
		a = a->getSig();
	}
}


string ListaSolicitudesContratos::mostrarTransacciones() {
	stringstream ss;
	ss << "Transacciones:" << "\n";
	int num = 1;
	NodoSolicitud* a = primero;
	while (a) {
		ss << num<<") " << a->getDato()->toResumen() << "\n";
		a = a->getSig();
	}
	ss << ++num << ") Regresar\n";
	return ss.str();
}
string ListaSolicitudesContratos::toString() const {
	// muestra todas las transacciones en detalle
	stringstream ss;
	if (!primero) {
		ss << "No hay transacciones disponibles.\n";
		return ss.str();
	}
	NodoSolicitud* a = primero;
	while (a) {
		ss << a->getDato()->toString() << "\n";
		a = a->getSig();
	}
	return ss.str();
}

// Muestra el listado filtrado
string ListaSolicitudesContratos::mostrarTransaccionesPorColaborador(string idColaborador) {
	stringstream ss;
	ss << "\nSolicitudes Pendientes para Colaborador (ID: " << idColaborador << "):\n";

	NodoSolicitud* actual = primero;
	int num = 1;
	bool encontrado = false;

	while (actual) {
		// Filtra por ID de Colaborador y Estado 1 (Pendiente)
		if (actual->getDato()->getIdColaborador() == idColaborador && actual->getDato()->getEstadoTransaccion() == 1) {
			ss << "------------------------------------------------------------\n";
			ss << num << ") " << actual->getDato()->toResumen() << " (Cod: " << actual->getDato()->getCodigoTransaccion() << ")\n";
			num++;
			encontrado = true;
		}
		actual = actual->getSig();
	}

	if (!encontrado) {
		ss << "------------------------------------------------------------\n";
		ss << "(No hay solicitudes pendientes gestionadas por este colaborador).\n";
		num = 1;
	}
	ss << "------------------------------------------------------------\n";
	ss << num << ") Regresar\n";

	return ss.str();
}

// Obtiene la transacción por índice en el listado filtrado, como me mostró
SolicitudAlquiler* ListaSolicitudesContratos::obtenerTransaccionFiltradaPorIndice(string idColaborador, int indice) {
	if (indice <= 0) return nullptr;

	NodoSolicitud* actual = primero;
	int contador = 0;

	while (actual) {
		// Filtra por ID de Colaborador y Estado 1 (Pendiente)
		if (actual->getDato()->getIdColaborador() == idColaborador && actual->getDato()->getEstadoTransaccion() == 1) {
			contador++;
			if (contador == indice) {
				return actual->getDato();
			}
		}
		actual = actual->getSig();
	}
	return nullptr;
}

// Muestra el listado filtrado por Cliente
string ListaSolicitudesContratos::mostrarTransaccionesPorCliente(string idCliente) {
	stringstream ss;
	ss << "Solicitudes Pendientes para Cliente (ID: " << idCliente << "):\n";
	
	NodoSolicitud* actual = primero;
	int num = 1;
	bool encontrado = false;

	while (actual) {
		// Filtra por ID de Cliente y Estado 1 (Pendiente)
		if (actual->getDato()->getIdCliente() == idCliente && actual->getDato()->getEstadoTransaccion() == 1) {
			ss << num << ") " << actual->getDato()->toResumen() << " (Cod: " << actual->getDato()->getCodigoTransaccion() << ")\n";
			num++;
			encontrado = true;
		}
		actual = actual->getSig();
	}

	if (!encontrado) {
		ss << "(No hay solicitudes pendientes realizadas por este cliente).\n";
		num = 1; 
	}

	ss << num << ") Regresar\n"; 
	
	return ss.str();
}

// Obtiene la transacción por índice en el listado filtrado por Cliente
SolicitudAlquiler* ListaSolicitudesContratos::obtenerTransaccionFiltradaPorIndiceCliente(string idCliente, int indice) {
	if (indice <= 0) return nullptr;

	NodoSolicitud* actual = primero;
	int contador = 0;

	while (actual) {
		// Filtra por ID de Cliente y Estado 1 (Pendiente)
		if (actual->getDato()->getIdCliente() == idCliente && actual->getDato()->getEstadoTransaccion() == 1) {
			contador++;
			if (contador == indice) {
				return actual->getDato();
			}
		}
		actual = actual->getSig();
	}
	return nullptr;
}

// Método para obtener reporte de contratos por cliente
string ListaSolicitudesContratos::obtenerReporteContratosCliente(string idCliente, int& contratosCount) const {
	stringstream ss;
	contratosCount = 0;

	NodoSolicitud* actual = primero;
	while (actual) {
		SolicitudAlquiler* sol = actual->getDato();
		// Filtra por ID de Cliente y Estado 2 (Contrato/Aprobado/Finalizado)
		if (sol->getIdCliente() == idCliente && sol->getEstadoTransaccion() == 2) {

			if (contratosCount > 0) {
				ss << ", "; // Separador
			}
			ss << sol->getCodigoTransaccion();
			contratosCount++;
		}
		actual = actual->getSig();
	}

	return ss.str();
}


// Método de filtrado de historial
string ListaSolicitudesContratos::mostrarHistorialCompletado() const {
	stringstream ss;
	ss << "Historial de Transacciones Finalizadas/Cerradas:\n";
	ss << "----------------------------------------------------\n";

	if (!primero) {
		ss << "(No hay transacciones en el historial).\n";
		return ss.str();
	}

	NodoSolicitud* actual = primero;
	bool encontrado = false;

	while (actual) {
		int estado = actual->getDato()->getEstadoTransaccion();
		// Filtra por estados 2 (Contrato/Aprobado), 3 (Rechazado), 4 (Anulado)
		if (estado == 2 || estado == 3 || estado == 4) {
			ss << actual->getDato()->toResumen() << " (Cod: " << actual->getDato()->getCodigoTransaccion() << ")\n";
			encontrado = true;
		}
		actual = actual->getSig();
	}

	if (!encontrado) {
		ss << "(No hay transacciones completadas, rechazadas o anuladas en este historial).\n";
	}

	ss << "----------------------------------------------------\n";

	return ss.str();
}


// --- IMPLEMENTACIÓN DE REPORTE DE CONTRATOS POR VEHÍCULO ESPECÍFICO ---

string ListaSolicitudesContratos::generarReporteContratosPorVehiculo(string placaVehiculo) const {
	stringstream ss;
	ss << "\n======= REPORTE DE CONTRATOS PARA VEHÍCULO ESPECÍFICO =======\n" << endl;
	ss << "Placa Solicitada: " << placaVehiculo << endl;
	ss << "-----------------------------------------------------------------" << endl;

	NodoSolicitud* actual = primero;
	bool encontrado = false;

	while (actual) {
		SolicitudAlquiler* sol = actual->getDato();

		// 1. Filtra por Placa y solo transacciones que sean Contratos (Estado 2)
		if (sol && sol->getPlacaVehiculo() == placaVehiculo && sol->getEstadoTransaccion() == 2) {

			ContratoAlquiler* contrato = dynamic_cast<ContratoAlquiler*>(sol);

			// 2. Determinar el estado detallado 
			string estadoDetallado = (contrato && contrato->getEstadoDetalladoStr() != "")
				? contrato->getEstadoDetalladoStr()
				: "Contrato Activo/Vigente";
			ss << "-----------------------------------------------------------------" << endl;
			ss << "\n--- Contrato CÓDIGO: " << sol->getCodigoTransaccion() << " ---\n";
			ss << "ID Cliente: " << sol->getIdCliente() << endl;
			ss << "Días de Alquiler: " << sol->getDiasAlquiler() << endl;
			ss << "Fecha de Inicio: " << sol->getFechaInicio() << endl;
			ss << "Fecha de Devolución: " << sol->getFechaEntrega() << endl;
			ss << "Estado de Contrato: " << estadoDetallado << endl;
			ss << "-----------------------------------------------------------------" << endl;

			encontrado = true;
		}
		actual = actual->getSig();
	}

	if (!encontrado) {
		ss << "No se encontraron contratos (Estado 2) asociados a la placa " << placaVehiculo << "." << endl;
	}
	ss << "======================================================================\n";

	return ss.str();
}

// Funcion auxiliar estatica para comparar fechas tm (tm1 > tm2 significa que tm1 es mas reciente)
static bool esMasReciente(tm tm1, tm tm2) {
	// Normalizar la estructura tm para asegurar comparacion correcta
	mktime(&tm1);
	mktime(&tm2);
	// Convertir a time_t para una comparacion simple
	time_t t1 = mktime(&tm1);
	time_t t2 = mktime(&tm2);
	return t1 > t2; // Retorna true si t1 es mas reciente
}


// Implementacion de generarReporteContratosOrdenado
string ListaSolicitudesContratos::generarReporteContratosOrdenado() const {
	stringstream ss;

	// 1. Contar y extraer los contratos (Estado 2) en un array dinamico
	int numContratos = 0;
	NodoSolicitud* actual = primero;
	while (actual) {
		if (actual->getDato()->getEstadoTransaccion() == 2) { // 2 = Contrato Activo
			numContratos++;
		}
		actual = actual->getSig();
	}

	if (numContratos == 0) {
		ss << "(No hay contratos activos para reportar)." << endl;
		return ss.str();
	}

	// Array dinamico de punteros a SolicitudAlquiler 
	SolicitudAlquiler** contratosArray = new SolicitudAlquiler * [numContratos];
	for (int i = 0; i < numContratos; i++) {
		contratosArray[i] = nullptr;
	}
	int indice = 0;
	actual = primero;
	while (actual) {
		if (actual->getDato()->getEstadoTransaccion() == 2) {
			contratosArray[indice++] = actual->getDato();
		}
		actual = actual->getSig();
	}

	// 2. Ordenar el array (Bubble Sort: mas reciente a mas antiguo)
	for (int i = 0; i < numContratos - 1; i++) {
		for (int j = 0; j < numContratos - i - 1; j++) {
			
			if (!esMasReciente(contratosArray[j]->getFechaInicioTM(), contratosArray[j + 1]->getFechaInicioTM())) {
				SolicitudAlquiler* temp = contratosArray[j];
				contratosArray[j] = contratosArray[j + 1];
				contratosArray[j + 1] = temp;
			}
		}
	}

	// 3. Generar el reporte 
	ss << "-----------------------------------------------------------------------------------------------------" << endl;
	ss << "| Codigo | Estado         | F. Inicio | F. Dev. | ID Cliente | Placa    | P. Diario | P. Total | ID Colab |" << endl;
	ss << "-----------------------------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < numContratos; i++) {
		SolicitudAlquiler* sol = contratosArray[i];

		if (sol) {
			// Formato manual con espaciado
			ss << "| " << sol->getCodigoTransaccion() << "    ";
			ss << "| Activo         ";
			ss << "| " << sol->getFechaInicio() << " ";
			ss << "| " << sol->getFechaEntrega() << " ";
			ss << "| " << sol->getIdCliente() << "   ";
			ss << "| " << sol->getPlacaVehiculo() << " ";
			ss << "| " << sol->getPrecioDiario() << "     ";
			ss << "| " << sol->getPrecioTotal() << "    ";
			ss << "| " << sol->getIdColaborador() << "  |" << endl;
		}
	}
	ss << "-----------------------------------------------------------------------------------------------------" << endl;

	delete[] contratosArray;

	return ss.str();
}