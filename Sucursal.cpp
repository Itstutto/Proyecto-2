#include "Sucursal.h"
#include "ContratoAlquiler.h"
#include "Carro.h"
#include "Cliente.h"
#include "Colaborador.h"
#include <iostream>

Sucursal::Sucursal() : numeroSucursal(0) {
	planteles = new ListaPlantel();
	clientes = new ListaClientes1();
	colaboradores = new ListaColaboradores1();
	solicitudes = new ListaSolicitudesContratos();
	contratos = new ListaSolicitudesContratos();
}

Sucursal::Sucursal(int numero) : numeroSucursal(numero) {
	planteles = new ListaPlantel();
	clientes = new ListaClientes1();
	colaboradores = new ListaColaboradores1();
	solicitudes = new ListaSolicitudesContratos();
	contratos = new ListaSolicitudesContratos();
}

Sucursal::~Sucursal() {
	delete planteles;
	delete clientes;
	delete colaboradores;
	delete solicitudes;
	delete contratos;
}

int Sucursal::getNumeroSucursal() const { return numeroSucursal; }
void Sucursal::setNumeroSucursal(int numero) { numeroSucursal = numero; }

ListaPlantel* Sucursal::getPlanteles() { return planteles; }
ListaClientes1* Sucursal::getClientes() { return clientes; }
ListaColaboradores1* Sucursal::getColaboradores() { return colaboradores; }
ListaSolicitudesContratos* Sucursal::getSolicitudes() { return solicitudes; }
ListaSolicitudesContratos* Sucursal::getContratos() { return contratos; }

Carro* Sucursal::buscarCarroPorPlaca(const string& placa)
{
	NodoPl* actual = planteles->getPrimero();
	while (actual) {
		Carro* carroEncontrado = actual->getDato()->getCarroxPlaca(placa);
		if (carroEncontrado) {
			return carroEncontrado;
		}
		actual = actual->getSig();
	}
	return nullptr; // No se encontró el carro en ningún plantel
}
bool Sucursal::modificarPrecioCategoria(char categoria, double nuevoPrecio) {
	if (categoria < 'A' || categoria > 'D' || nuevoPrecio < 0) {
		return false; // Categoría inválida o precio negativo
	}
	switch (categoria) {
	case 'A':
		Carro::precioA = nuevoPrecio;
		break;
	case 'B':
		Carro::precioB = nuevoPrecio;
		break;
	case 'C':
		Carro::precioC = nuevoPrecio;
		break;
	case 'D':
		Carro::precioD = nuevoPrecio;
		break;
	default:
		return false;
	}
	planteles->modificarPrecioCategoria(categoria);
}

//usar "endl" en vez de \n (aplica en todo)
string Sucursal::mostrarOpciones() {
	stringstream ss;
	ss << "-------------------------------------------------" << endl;
	ss << "Sucursal Numero: " << numeroSucursal << endl
		<< "1. Clientes" << endl
		<< "2. Colaboradores" << endl
		<< "3. Planteles" << endl
		<< "4. Contratos" << endl
		<< "5. Regresar al menu principal" << endl;
	ss << "-------------------------------------------------" << endl;
	ss << "Seleccione una opcion: ";
	return ss.str();
}

// Implementación 2: Método de Conversión Crítico
bool Sucursal::convertirSolicitudAContrato(int idSolicitud, const string& idColaboradorAprueba,
	ListaSolicitudesContratos* listaSolicitudes,
	ListaSolicitudesContratos* listaContratos,
	ListaClientes1* listaClientes,
	ListaColaboradores1* listaColaboradores) {

	// 1. Validar la Solicitud
	SolicitudAlquiler* solicitud = listaSolicitudes->buscarTransaccionPorCodigo(idSolicitud);

	if (!solicitud || solicitud->getEstadoTransaccion() != 1) {
		cout << "ERROR: Solicitud con ID " << idSolicitud << " no es Pendiente o no existe." << endl;
		return false;
	}

	// 2. Validar Colaborador Aprobador
	Colaborador* colabAprobador = dynamic_cast<Colaborador*>(listaColaboradores->buscarPersona(idColaboradorAprueba));
	if (!colabAprobador) {
		cout << "ERROR: ID de Colaborador aprobador '" << idColaboradorAprueba << "' no es valido. Operacion cancelada." << endl;
		return false;
	}

	// 3. Validar Carro y Disponibilidad (CRÍTICO)
	string placaCarro = solicitud->getPlacaVehiculo();
	Carro* carro = buscarCarroPorPlaca(placaCarro);

	if (!carro) {
		cout << "ERROR: El carro con placa " << placaCarro << " no existe en la sucursal. Solicitud cancelada." << endl;
		// La solicitud debe ser eliminada/rechazada si el carro ya no está.
		solicitud->setEstadoTransaccion(3); // Estado 3: Rechazada
		listaSolicitudes->eliminarTransaccionPorCodigo(idSolicitud);
		return false;
	}
	
	// VALIDACIÓN DE ESTADO: Impedir conversión si el carro NO está "Disponible"
	if (carro->getEstadoCarro() != "Disponible") {
		cout << "AVISO: El carro " << placaCarro << " NO esta disponible (Estado: " << carro->getEstadoCarro() << ")." << endl;
		cout << "Solicitud " << solicitud->getCodigoTransaccion() << " cancelada y marcada como RECHAZADA." << endl;

		// Actualizar historiales a Rechazada (3)
		Cliente* cli = dynamic_cast<Cliente*>(solicitud->getCliente());
		Colaborador* col = dynamic_cast<Colaborador*>(solicitud->getColaborador());
		if (cli) cli->getHistorial()->buscarTransaccionPorCodigo(idSolicitud)->setEstadoTransaccion(3);
		if (col) col->getHistorial()->buscarTransaccionPorCodigo(idSolicitud)->setEstadoTransaccion(3);

		listaSolicitudes->eliminarTransaccionPorCodigo(idSolicitud);
		return false;
	}
	
	// --- CONVERSIÓN EXITOSA ---

	// 4. Crear el Contrato (Requiere el constructor copia)
	ContratoAlquiler* nuevoContrato = new ContratoAlquiler(*solicitud);
	
	// Establecer colaborador aprobador en el contrato
	nuevoContrato->setColaborador(colabAprobador);
	const int ESTADO_CONTRATO_ACTIVO = 2; 
	nuevoContrato->setEstadoTransaccion(ESTADO_CONTRATO_ACTIVO); 
	// EstadoDetallado por defecto podría ser 'Pendiente de Ejecución' (2)
	nuevoContrato->setEstadoDetallado(2, "Pendiente de Ejecucion");

	// 5. Marcar el Carro como "Alquilado" (Estado 2) y registrar el colaborador
	const int ESTADO_CARRO_ALQUILADO = 2;
	carro->setEstadosCarro(ESTADO_CARRO_ALQUILADO, idColaboradorAprueba); // Este método actualiza la Bitácora del carro.

	// 6. Insertar el nuevo Contrato en la lista de Contratos de la sucursal
	listaContratos->insertarFinal(nuevoContrato);

	// 7. Actualizar historiales a Contrato Activo (Estado 2)
	Cliente* cli = dynamic_cast<Cliente*>(listaClientes->buscarPersona(solicitud->getIdCliente()));
	Colaborador* col = dynamic_cast<Colaborador*>(listaColaboradores->buscarPersona(solicitud->getIdColaborador())); // Colaborador que la registró
	
	if (cli) cli->getHistorial()->buscarTransaccionPorCodigo(idSolicitud)->setEstadoTransaccion(ESTADO_CONTRATO_ACTIVO);
	if (col) col->getHistorial()->buscarTransaccionPorCodigo(idSolicitud)->setEstadoTransaccion(ESTADO_CONTRATO_ACTIVO);

	// 8. Eliminar la Solicitud original de la lista de Solicitudes Pendientes
	listaSolicitudes->eliminarTransaccionPorCodigo(idSolicitud);

	cout << "EXITO: Solicitud " << idSolicitud << " convertida a Contrato "
		 << nuevoContrato->getCodigoTransaccion() << " exitosamente." << endl;
	return true;
}


// --- REPORTE DE PORCENTAJE DE OCUPACIÓN DE LOS PLANTELES ---
string Sucursal::generarReporteOcupacionPlanteles() { 
	stringstream ss;
	ss << "\n======= REPORTE DE OCUPACION DE PLANTELES - Sucursal " << numeroSucursal << " =======\n";

	NodoPl* actual = planteles->getPrimero();
	bool encontrado = false;

	while (actual) {
		Plantel* p = actual->getDato();
		if (p) {
			ss << p->getDatosOcupacionStr() << endl; 
			encontrado = true;
		}
		actual = actual->getSig();
	}

	if (!encontrado) {
		ss << "(No hay planteles registrados en esta sucursal)." << endl;
	}

	ss << "======================================================================\n";
	return ss.str();
}