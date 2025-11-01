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
	    << "Actividad economica: " << actividadEconomica
	    << "% Descuento: " << porcentajeDescuento
		<< "----------------------------------------------" << endl;
	return ss.str();
}

string ClienteJuridico::infoMenu() const {
	stringstream s;
	//muestra solo el nombre y el id, para el menu
	s << "Cliente Juridico - ID: " << getId() << endl
		<< "    Nombre: " << getNombre();
	return s.str();
}

string ClienteJuridico::mostrarModificar() const
{
	stringstream s;
	s<< Cliente::mostrarModificar()
		<< "4. Actividad economica: " << actividadEconomica << endl
		<< "5. Porcentaje de descuento: " << porcentajeDescuento << endl
		<< "6. Salir" << endl;
	return s.str();
}
