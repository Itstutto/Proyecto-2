#pragma once
#include "Cliente.h"

class ClienteFisico : public Cliente {
public:
	ClienteFisico();
	ClienteFisico(string nombre, string id, string paisResidencia);
	virtual ~ClienteFisico();

	string toString() const override;
	string infoMenu() const override;
	string mostrarModificar() const override;
};
