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
