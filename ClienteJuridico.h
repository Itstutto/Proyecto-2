#pragma once
#include "Cliente.h"

class ClienteJuridico : public Cliente {
private:
	string actividadEconomica;
	double porcentajeDescuento; // 0.0 - 100.0
public:
	ClienteJuridico();
	ClienteJuridico(string nombre, string id, string paisResidencia,
				  string actividadEconomica, double porcentajeDescuento);
	virtual ~ClienteJuridico();

	string getActividadEconomica();
	void setActividadEconomica(string act);
	double getPorcentajeDescuento();
	void setPorcentajeDescuento(double pct);

	string toString() const override;
};
