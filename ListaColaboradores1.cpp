#include "ListaColaboradores1.h"
#include "ListaSolicitudesContratos.h"
ListaColaboradores1::ListaColaboradores1() : ListaPersonas() {}
void ListaColaboradores1::eliminarClienteHistorial(string id)
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
ListaColaboradores1::~ListaColaboradores1() {}
string ListaColaboradores1::mostrarPersonas(int ver) {
	stringstream ss;
	ss << endl << "Colaboradores" << endl;
	int cant = 1;
	NodoP* actual = primero;
	while (actual) {
		ss << "--------------------------------------------------------------------------------------------------------------" << endl
			<<cant++<<"). " << actual->getDato()->toString() << "\n";
		actual = actual->getSig();
	}
	if (ver == 0) {
		ss << "--------------------------------------------------------------------------------------------------------------" << endl
			<<cant++<<"). " << "Agregar Colaborador\n"
			<< "--------------------------------------------------------------------------------------------------------------" << endl;
		ss << cant++ << "). " << "Eliminar Colaborador\n";
			
	}
	ss << "--------------------------------------------------------------------------------------------------------------" << endl;
	ss << cant++ << "). " << "Regresar\n"
		<< "--------------------------------------------------------------------------------------------------------------" << endl
		<< "Seleccione una opcion: ";
	return ss.str();
}
