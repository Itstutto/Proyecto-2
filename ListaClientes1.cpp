#include "ListaClientes1.h"
#include "ListaSolicitudesContratos.h"
#include "ClienteFisico.h"
#include "ClienteJuridico.h"

ListaClientes1::ListaClientes1() : ListaPersonas() {}
ListaClientes1::~ListaClientes1() {}

void ListaClientes1::eliminarColaboradorHistorial(string id)
{
	NodoP* actual = primero;
	while (actual) {
		Persona* p = actual->getDato();
		if (p) {
			ListaSolicitudesContratos* historial = p->getHistorial();
			if (historial) {
				historial->clienteEliminado(id);
			}
		}
		actual = actual->getSig();
	}
}

string ListaClientes1::mostrarPersonas(int ver) {
	stringstream ss;
	int opcion = 1;
	ss << "Clientes" << endl << endl;
	NodoP* actual = primero;
	while (actual) {
		ss << opcion<<"). " << actual->getDato()->infoMenu() << endl
			<< "---------------------------------------------------------"<<endl;
		actual = actual->getSig();
		opcion++;
	}
	if (ver == 0) {
		ss<<opcion++<<"). Reporte de clientes" << endl
			<< "----------------------------------------------------------" << endl;
		ss << opcion++ << "). Agregar nuevo cliente" << endl
			<< "----------------------------------------------------------" << endl;
		ss << opcion++ << "). Eliminar cliente" << endl
			<< "----------------------------------------------------------" << endl;
	}
		ss << opcion << "). Salir" << endl;
	return ss.str();
}

string ListaClientes1::generarReporteClientes() {
	stringstream ss;
	ss << "Reporte de Clientes" << endl << endl;
	NodoP* actual = primero;
	int total = 0, fisicos = 0, juridicos = 0;

	if (!actual) {
		ss << "No hay clientes registrados." << endl;
		return ss.str();
	}

	while (actual) {
		Persona* p = actual->getDato();
		if (p) {
			Cliente* c = dynamic_cast<Cliente*>(p);
			if (c) {
				ss << "- " << c->toString() << endl;

				ClienteJuridico* cj = dynamic_cast<ClienteJuridico*>(c);
				if (cj) {
					juridicos++;
				} else {
					fisicos++;
				}

				ListaSolicitudesContratos* hist = c->getHistorial();
				if (hist) {
					ss << "  Transacciones registradas: " << hist->getTam() << endl;
				}
				ss << "----------------------------------------------------------" << endl;
				total++;
			}
		}
		actual = actual->getSig();
	}

	ss << "Totales: " << total << " clientes (Fisicos: " << fisicos << ", Juridicos: " << juridicos << ")" << endl;
	return ss.str();
}
