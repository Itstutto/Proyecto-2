#include "SolicitudAlquiler.h"
#include "ClienteJuridico.h"
int SolicitudAlquiler::consecutivo = 0;

//constructo
SolicitudAlquiler::SolicitudAlquiler() : cliente(nullptr), colaborador(nullptr), vehiculo(nullptr), diasAlquiler(0),
	  precioDiario(0.0), precioTotal(0.0), estadoTransaccion(1), tipoTransaccion('S') {
	codigoTransaccion = ++consecutivo;
	// Inicializar fechas a cero
	fechaInicio = {};
	fechaEntrega = {};
}
SolicitudAlquiler::SolicitudAlquiler(Persona* cliente, Persona* colaborador, Carro* Vehiculo, int dias,
									 const int& inicio, const int& entrega, double precioDiario, double precioTotal, char tipoTransaccion ,int estado)
	: cliente(cliente), colaborador(colaborador), vehiculo(Vehiculo), diasAlquiler(dias),
	  precioDiario(precioDiario), precioTotal(precioTotal), estadoTransaccion(estado), tipoTransaccion(tipoTransaccion) {
	// Generar codigo de transaccion basado en el consecutivo
	codigoTransaccion = ++consecutivo;
	// Configurar fechaInicio desde el int
	int diaInicio = inicio / 1000000;
	int mesInicio = (inicio / 10000) % 100;
	int anioInicio = inicio % 10000;
	fechaInicio.tm_mday = diaInicio;
	fechaInicio.tm_mon = mesInicio - 1; // tm_mon es 0-11
	fechaInicio.tm_year = anioInicio - 1900; // tm_year es años desde 1900
	// Configurar fechaEntrega desde el int
	int diaEntrega = entrega / 1000000;
	int mesEntrega = (entrega / 10000) % 100;
	int anioEntrega = entrega % 10000;
	fechaEntrega.tm_mday = diaEntrega;
	fechaEntrega.tm_mon = mesEntrega - 1; // tm_mon es 0-11
	fechaEntrega.tm_year = anioEntrega - 1900; // tm_year es años desde 1900

}


SolicitudAlquiler::~SolicitudAlquiler() {
	// No se eliminan cliente, colaborador ni vehiculo porque son gestionados externamente, se asignan a nullptr
	cliente = nullptr;
	colaborador = nullptr;
	vehiculo = nullptr;
}

string SolicitudAlquiler::getCodigoTransaccion() const { 
	stringstream s;
	s << tipoTransaccion<<codigoTransaccion;
	return s.str();
}
int SolicitudAlquiler::getCodigoTransaccionInt() const
{
	return codigoTransaccion;
}
int  SolicitudAlquiler::getEstadoTransaccion() const { return estadoTransaccion; }

// IMPLEMENTACIÓN DEL SETTER PARA EL ESTADO GENERAL DE LA TRANSACCIÓN
void SolicitudAlquiler::setEstadoTransaccion(int nuevoEstado) {
	if (nuevoEstado >= 1 && nuevoEstado <= 4) {
		estadoTransaccion = nuevoEstado;
	}
}

string SolicitudAlquiler::toResumen() const {
	stringstream ss;
	ss << tipoTransaccion << codigoTransaccion << " - " << vehiculo->getPlaca() << " - Cliente: " << cliente->getId() << " - Estado: " << estadoTransaccion;
	return ss.str();
}

Persona* SolicitudAlquiler::getCliente() const { return cliente; }
Persona* SolicitudAlquiler::getColaborador() const { return colaborador; }
Carro* SolicitudAlquiler::getCarro() const { return vehiculo; }
tm SolicitudAlquiler::getFechaInicioTM() const { return fechaInicio; }
tm SolicitudAlquiler::getFechaEntregaTM() const { return fechaEntrega; }



string SolicitudAlquiler::getIdCliente() const { return cliente->getId(); }
string SolicitudAlquiler::getIdColaborador() const { return colaborador->getId(); }
string SolicitudAlquiler::getPlacaVehiculo() const { return vehiculo->getPlaca(); }
int SolicitudAlquiler::getDiasAlquiler() const { return diasAlquiler; }
string SolicitudAlquiler::getFechaInicio() const {
	stringstream s;
	s << fechaInicio.tm_mday << "/" << fechaInicio.tm_mon + 1 << "/" << fechaInicio.tm_year + 1900;
	return s.str();
}
string SolicitudAlquiler::getFechaEntrega() const {
	stringstream s;
	s << fechaEntrega.tm_mday << "/" << fechaEntrega.tm_mon + 1 << "/" << fechaEntrega.tm_year + 1900;
	return s.str();
}
double SolicitudAlquiler::getPrecioDiario() const { return precioDiario; }
double SolicitudAlquiler::getPrecioTotal() const { return precioTotal; }
void SolicitudAlquiler::setCliente(Persona* p) {
	// verificar que sea un cliente
	Cliente* c = dynamic_cast<Cliente*>(p);
	if (c) {
		cliente = p;
	}

}
void SolicitudAlquiler::setColaborador(Colaborador* c) {
	// verificar que sea un colaborador
	Colaborador* col = dynamic_cast<Colaborador*>(c);
	if (col) {
		colaborador = c;
	}
}
void SolicitudAlquiler::setCarro(Carro* c) { vehiculo = c; }
void SolicitudAlquiler::setDiasAlquiler(int dias) { diasAlquiler = dias; }
//int 
void SolicitudAlquiler::setFechaInicio(const int& inicio) {
	// el int es pasado en formato DDMMYYYY ej 25062023 == 25/06/2023
	int dia = inicio / 1000000;
	int mes = (inicio / 10000) % 100;
	int anio = inicio % 10000;
	fechaInicio.tm_mday = dia;
	fechaInicio.tm_mon = mes - 1; // tm_mon es 0-11
	fechaInicio.tm_year = anio - 1900; // tm_year es años desde 1900
}
void SolicitudAlquiler::setFechaEntrega(const int& entrega) {
	// el int es pasado en formato DDMMYYYY ej 25062023 == 25/06/2023
	int dia = entrega / 1000000;
	int mes = (entrega / 10000) % 100;
	int anio = entrega % 10000;
	fechaEntrega.tm_mday = dia;
	fechaEntrega.tm_mon = mes - 1; // tm_mon es 0-11
	fechaEntrega.tm_year = anio - 1900; // tm_year es años desde 1900
}
void SolicitudAlquiler::setPrecioDiario(double precio) { precioDiario = precio; }
void SolicitudAlquiler::setPrecioTotal(double precio) { 
	precioTotal = precio * diasAlquiler;
	//aplica descuento si es cliente juridico
	if (!cliente) return;
	ClienteJuridico* cj = dynamic_cast<ClienteJuridico*>(cliente);
	if (cj) {
		double descuento = cj->getPorcentajeDescuento(); // obtener el porcentaje de descuento
		precioTotal = precioTotal * (1 - descuento / 100.0); // aplicar descuento
	}

} // calcular total basado en diasAlquiler

void SolicitudAlquiler::calcularFechaEntrega()
{
	// Crear una copia de la fecha de inicio para manipular
	tm fechaCalculo = fechaInicio;
	// Sumar los diasAlquiler a la fecha de inicio
	fechaCalculo.tm_mday += diasAlquiler;
	// Normalizar la fecha (manejar desbordamientos de dias/meses)
	mktime(&fechaCalculo);
	// Actualizar la fechaEntrega con la fecha calculada
	fechaEntrega = fechaCalculo;
}

