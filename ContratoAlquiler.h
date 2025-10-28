#pragma once
#include "SolicitudAlquiler.h"

class ContratoAlquiler : public SolicitudAlquiler {
private:
	// Nuevos atributos para el manejo de sub-estados complejos de Contrato
	int estadoDetalladoContrato; // 1=Aprobado en alquiler, 2=Pendiente de Ejecución, 3=Finalizado
	string detalleFinalizacion;  // Guarda el detalle si es Finalizado (multa, reintegro, sin cargos)
public:

	//constructor copia de una solicitud aprobada
	ContratoAlquiler(const SolicitudAlquiler& solicitudAprobada);
	~ContratoAlquiler() override;

	// Getters y Setters para el estado detallado
	int getEstadoDetallado() const;
	string getEstadoDetalladoStr() const; // Devuelve el estado en texto
	void setEstadoDetallado(int nuevoEstado, const string& detalle = "");

	string toString() const override;
};
