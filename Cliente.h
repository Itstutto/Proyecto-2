#pragma once
#include "Persona.h"
#include <string>
#include <sstream>

using namespace std;

class ListaSolicitudesContratos; // forward declaration

class Cliente : public Persona {
protected:
	string paisResidencia;
public:
	Cliente();
	Cliente(string nombre, string id, string paisResidencia);
	virtual ~Cliente();

	string getPaisResidencia();
	void setPaisResidencia(string pais);
	string toString() const override; // virtual para ser sobrescrito
	string mostrarCliente() const;
	virtual string mostrarModificar() const override;

	// Muestra la lista de solicitudes PENDIENTES realizadas por este cliente.
	string mostrarSolicitudesPendientesRealizadas(ListaSolicitudesContratos* lsc);
};
