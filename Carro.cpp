#include "Carro.h"

double Carro::precioA = 20000;
double Carro::precioB = 27000;
double Carro::precioC = 45000;
double Carro::precioD = 34000;


Carro::Carro() {
	placa = "";
	modelo = "";
	marca = "";
	ubicacion = "";
	tipoLicencia = "";
	categoria = ' ';
	precioDiario = 0.0;
	historialEstados = new ListaBitacora();
	// estado inicial: Revision (4)
	historialEstados->insertarFinal(new EstadoBitacora(4, 4, "SISTEMA"));
}

Carro::Carro(string placa, string modelo, string marca, string ubicacion, string tipoLicencia, char catergoria) {
	this->placa = placa;
	this->modelo = modelo;	
	this->marca = marca;
	this->ubicacion = ubicacion;
	this->tipoLicencia = tipoLicencia;
	this->categoria = catergoria;
	switch (catergoria) {
		case 'A':
			this->precioDiario = precioA;
			break;
		case 'B':
			this->precioDiario = precioB;
			break;
		case 'C':
			this->precioDiario = precioC;
			break;
		case 'D':
			this->precioDiario = precioD;
			break;
		default:
			this->precioDiario = 0.0; // Categoria invalida
			break;
	}
	this->historialEstados = new ListaBitacora();
	// estado inicial: Revision (4)
	historialEstados->insertarFinal(new EstadoBitacora(4, 4, "SISTEMA"));
}

Carro::~Carro()
{
	delete historialEstados;
}

string Carro::getPlaca() { return placa; }
string Carro::getModelo() { return modelo; }
string Carro::getMarca() { return marca; }
string Carro::getUbicacion() { return ubicacion; }
string Carro::getTipoLicencia() { return tipoLicencia; }
char Carro::getCategoria() { return categoria; }
double Carro::getPrecioDiario() { return precioDiario; }

string Carro::getEstadoCarro()
{
	EstadoBitacora* ult = historialEstados->getUltimoEstado();
	int e = ult ? ult->getEstadoActual() : 4; // por defecto Revision
	switch (e) {
		case 1: return "Disponible";
		case 2: return "Alquilado";
		case 3: return "Devuelto";
		case 4: return "Revision";
		case 5: return "Lavado";
		default: return "Revision";
	}
}

string Carro::getHistorialEstados()
{
	stringstream s;
	s << historialEstados->mostrarBitacora();
	return s.str();
}

void Carro::setPlaca(string p) { placa = p; }
void Carro::setModelo(string m) { modelo = m; }
void Carro::setMarca(string ma) { marca = ma; }
void Carro::setUbicacion(string u) { ubicacion = u; }
void Carro::setTipoLicencia(string t) { tipoLicencia = t; }
void Carro::setCategoria(char c) { 
	categoria = c;
	actualizarPrecioDiario();
}

void Carro::actualizarPrecioDiario()
{
	switch (categoria) {
	case 'A':
		this->precioDiario = precioA;
		break;
	case 'B':
		this->precioDiario = precioB;
		break;
	case 'C':
		this->precioDiario = precioC;
		break;
	case 'D':
		this->precioDiario = precioD;
		break;
	default:
		this->precioDiario = 0.0; // Categoria invalida
		break;
	}
}

static bool transicionValida(int actual, int nuevo) {
	// Matriz corregida
	switch (actual) {
	case 1: return (nuevo == 2 || nuevo == 4 || nuevo == 5); // Disponible -> {Alquilado, Revision, Lavado}
	case 2: return (nuevo == 3); // Alquilado -> {Devuelto}
	case 3: return (nuevo == 4 || nuevo == 5); // Devuelto -> {Revision, Lavado}
	case 4: return (nuevo == 5); // Revision -> {Lavado}
	case 5: return (nuevo == 1 || nuevo == 4); // Lavado -> {Disponible, Revision}
	default: return false;
	}
}


int Carro::setEstadosCarro(int estado, string idColaborador)
{
	EstadoBitacora* ult = historialEstados->getUltimoEstado();
	int actual = ult ? ult->getEstadoActual() : 4; // Revision por defecto
	if (estado == actual) return -2;
	if (!transicionValida(actual, estado)) return -1;
	historialEstados->insertarFinal(new EstadoBitacora(actual, estado, idColaborador));
	return 1;
}

string Carro::toString() {
	stringstream ss;
	ss << "---------------------------------------------------------------------------" << endl;
	ss << "Carro [Placa: " << placa << ", Modelo: " << modelo << ", Marca: " << marca
		<< ", Ubicacion: " << ubicacion << ", Tipo Licencia: " << tipoLicencia
		<< ", Categoria: " << categoria << ", Precio Diario: " << precioDiario << "]"<<endl
		<< getHistorialEstados();
	ss << "---------------------------------------------------------------------------" << endl;
	return ss.str();
}