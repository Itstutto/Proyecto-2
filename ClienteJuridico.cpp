#include "ClienteJuridico.h"
#include <sstream>

ClienteJuridico::ClienteJuridico() : Cliente(), actividadEconomica(""), porcentajeDescuento(0.0) {}

ClienteJuridico::ClienteJuridico(string nombre, string id, string paisResidencia,
								   string actividadEconomica, double porcentajeDescuento)
	: Cliente(nombre, id, paisResidencia), actividadEconomica(actividadEconomica), porcentajeDescuento(porcentajeDescuento) {}

ClienteJuridico::~ClienteJuridico() {}

string ClienteJuridico::getActividadEconomica() { return actividadEconomica; }
void ClienteJuridico::setActividadEconomica(string act) { this->actividadEconomica = act; }

double ClienteJuridico::getPorcentajeDescuento() { return porcentajeDescuento; }
void ClienteJuridico::setPorcentajeDescuento(double pct) { this->porcentajeDescuento = pct; }

string ClienteJuridico::toString() const {
	stringstream ss;
	ss << "Cliente Juridico - " << Cliente::toString()
	   << ", Actividad economica: " << actividadEconomica
	   << ", % Descuento: " << porcentajeDescuento;
	return ss.str();
}
