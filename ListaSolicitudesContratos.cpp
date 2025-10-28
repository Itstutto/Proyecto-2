#include "ListaSolicitudesContratos.h"

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
			Carro* c = new Carro(temp->getPlaca() + " ELIMINADO", temp->getModelo() + " ELIMINADO",temp->getMarca()+" ELIMINADO", "Basurero", "N/A", '0', '0');
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
