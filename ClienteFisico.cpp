#include "ClienteFisico.h"
#include <sstream>

ClienteFisico::ClienteFisico() : Cliente() {}

ClienteFisico::ClienteFisico(string nombre, string id, string paisResidencia)
	: Cliente(nombre, id, paisResidencia) {}

ClienteFisico::~ClienteFisico() {}

string ClienteFisico::toString() const {
	stringstream ss;
	ss << "Cliente Fisico - " << Cliente::toString();
	return ss.str();
}
string ClienteFisico::infoMenu() const {
	stringstream s;
	//muestra solo el nombre y el id, para el menu
	s << "Cliente Fisico - Nombre: " << getNombre() << ", ID: " << getId();
	return s.str();
}

string ClienteFisico::mostrarModificar() const
{
	stringstream s;
	s << Cliente::mostrarModificar()<< endl
		<< "4. Salir" << endl;
	return s.str();
}
