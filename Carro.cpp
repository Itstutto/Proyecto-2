#include "Carro.h"

Carro::Carro() {
	placa = "";
	modelo = "";
	marca = "";
	ubicacion = "";
	categoria = ' ';
	estadosCarro = new ListaEstados();
	estadosCarro->insertarInicio("Revision");
}

Carro::Carro(string placa, string modelo, string marca, string ubicacion, string tipoLicencia, char catergoria) {
	this->placa = placa;
	this->modelo = modelo;	
	this->marca = marca;
	this->ubicacion = ubicacion;
	this->tipoLicencia = tipoLicencia;
	this->categoria = catergoria;
	this->estadosCarro = new ListaEstados();
	estadosCarro->insertarInicio("Revision");
}

Carro::~Carro()
{
	delete estadosCarro;
}

string Carro::getPlaca() {
	return placa;
}
string Carro::getModelo() {
	return modelo;
}
string Carro::getMarca() {
	return marca;
}
string Carro::getUbicacion() {
	return ubicacion;
}
string Carro::getTipoLicencia() {
	return tipoLicencia;
}
char Carro::getCategoria() {
	return categoria;
}

string Carro::getEstadoCarro()
{
	return estadosCarro->getPrimero()->getEstado();
}

string Carro::getHistorialEstados()
{
	stringstream s;

	s << estadosCarro->mostrarEstados();
	return s.str();
}




void Carro::setPlaca(string p) {
	placa = p;
}
void Carro::setModelo(string m) {
	modelo = m;
}
void Carro::setMarca(string ma) {
	marca = ma;
}
void Carro::setUbicacion(string u) {
	ubicacion = u;
}
void Carro::setTipoLicencia(string t) {
	tipoLicencia = t;
}
void Carro::setCategoria(char c) {
	categoria = c;
}

int Carro::setEstadosCarro(int estado)
{
	// Disponible, Alquilado, Devuelto, Revisión, Lavado

	string estadoStr;
	switch (estado) {
	case 1:
		if (getEstadoCarro() == "Devuelto" ||
			getEstadoCarro() == "Revision") return -1; //error -1, no puede ir de Devuelto o Revisión a Disponible
		if (getEstadoCarro() == "Disponible") return -2; //error -2, ya está en Disponible
		estadoStr = "Disponible";
		break;
	case 2:
		if (getEstadoCarro() == "Devuelto" || 
			getEstadoCarro() == "Revision" ||
			getEstadoCarro() == "Lavado") return -1; //error -1, no puede ir de Devuelto, Revisión o Lavado a Alquilado
		if (getEstadoCarro() == "Alquilado") return -2; //error -2, ya está en Alquilado
		estadoStr = "Alquilado";
		break;
	case 3:
		if (getEstadoCarro() != "Alquilado") return -1; //error -1, solo puede ir de Alquilado a Devuelto
		if (getEstadoCarro() == "Devuelto") return -2; //error -2, ya está en Devuelto
		estadoStr = "Devuelto";
		break;
	case 4:
		if (getEstadoCarro() == "Alquilado") return -1; //error -1, no puede ir de Alquilado a Revisión
		if (getEstadoCarro() == "Revision") return -2; //error -2, ya está en Revisión
		estadoStr = "Revisión";
		break;
	case 5:
		if (getEstadoCarro() == "Alquilado") return -1; //error -1, no puede ir de Alquilado a Lavado
		if (getEstadoCarro() == "Lavado") return -2; //error -2, ya está en Lavado 
		estadoStr = "Lavado";
		break;
	default:
		return false; //error 0, opción inválida
	}


	estadosCarro->insertarInicio(estadoStr);
	return true;

}

string Carro::toString() {
	stringstream ss;
	ss << "---------------------------------------------------------------------------" << endl;
	ss << "Carro [Placa: " << placa << ", Modelo: " << modelo << ", Marca: " << marca
		<< ", Ubicacion: " << ubicacion << ", Tipo Licencia: " << tipoLicencia
		<< ", Categoria: " << categoria << "]"<<endl
		<< "Estados del Carro: " << estadosCarro->mostrarEstados();
	ss << "---------------------------------------------------------------------------" << endl;
	return ss.str();
}