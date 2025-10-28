#include "ListaClientes1.h"
#include "ListaSolicitudesContratos.h"
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
