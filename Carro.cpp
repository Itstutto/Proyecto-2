#include "Carro.h"

Carro::Carro() {
	placa = "";
	modelo = "";
	marca = "";
	ubicacion = "";
	categoria = ' ';
}

Carro::Carro(string placa, string modelo, string marca, string ubicacion, string tipoLicencia, char catergoria) {
	this->placa = placa;
	this->modelo = modelo;	
	this->marca = marca;
	this->ubicacion = ubicacion;
	this->tipoLicencia = tipoLicencia;
	this->categoria = catergoria;
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

string Carro::toString() {
	stringstream ss;
	ss << "Carro [Placa: " << placa << ", Modelo: " << modelo << ", Marca: " << marca
		<< ", Ubicacion: " << ubicacion << ", Tipo Licencia: " << tipoLicencia
		<< ", Categoria: " << categoria << "]";
	return ss.str();
}