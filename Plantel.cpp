#include "Plantel.h"

Plantel::Plantel() : identificador('-'), filas(0), columnas(0), estacionamiento(nullptr) {}

Plantel::Plantel(char id, int f, int c) : identificador(id), filas(f), columnas(c) {
	estacionamiento = new Carro**[filas];
	for (int i = 0; i < filas; ++i) {
		estacionamiento[i] = new Carro*[columnas];
		for (int j = 0; j < columnas; ++j) {
			estacionamiento[i][j] = nullptr;
		}
	}
}

Plantel::~Plantel() {
	for (int i = 0; i < filas; ++i) {
		for (int j = 0; j < columnas; ++j) {
			delete estacionamiento[i][j];
		}
		delete[] estacionamiento[i];
	}
	delete[] estacionamiento;
}

char Plantel::getIdentificador() {
	return identificador;
}
int Plantel::getFilas() {
	return filas;
}
int Plantel::getColumnas() {
	return columnas;
}

Carro* Plantel::getCarroxPos(int f, int c) {
	if (f >= 0 && f < filas && c >= 0 && c < columnas) {
		return estacionamiento[f][c];
	}
	return nullptr;
}
Carro* Plantel::getCarroxPlaca(string placa) {
	for (int i = 0; i < filas; ++i) {
		for (int j = 0; j < columnas; ++j) {
			if (estacionamiento[i][j] && estacionamiento[i][j]->getPlaca() == placa) {
				return estacionamiento[i][j];
			}
		}
	}
	return nullptr;
}

bool Plantel::moverCarro(string placa, Plantel* destino)
{
	// solo se usa para mover carros a plantel de alquiler
	Carro* carro = getCarroxPlaca(placa);
	if (!carro) return false; // Carro no encontrado
	if (!destino->agregarCarro(carro)) return false; // No se pudo agregar al destino
	carro->setUbicacion("En alquiler");
	desvincularCarro(placa); // Elimina sin borrar el carro
	return true;
}

int Plantel::getCanTotal()
{
	return filas * columnas;
}

int Plantel::getCanDisponibles()
{
	int disponibles = 0;
	for (int i = 0; i < filas; ++i) {
		for (int j = 0; j < columnas; ++j) {
			if (estacionamiento[i][j] == nullptr) {
				disponibles++;
			}
		}
	}
	return disponibles;
}

string Plantel::getEspacioEstacionamiento(int f, int c) {
	stringstream s;

	s << identificador << f << c;
	return s.str();
}

void Plantel::setIdentificador(char id) {
	identificador = id;
}
void Plantel::setFilas(int f) {
	filas = f;
}
void Plantel::setColumnas(int c) {
	columnas = c;
}
bool Plantel::agregarCarro(Carro* carro, int f, int c) {

	if (f < 0 || f >= filas || c < 0 || c >= columnas) return false;
	if (estacionamiento[f][c]) return false; // Espacio ya ocupado
	estacionamiento[f][c] = carro;
	stringstream s;
	s << "Plantel " << identificador << f << c;
	carro->setUbicacion(s.str());
	return true;
}

bool Plantel::agregarCarro(Carro* carro)
{
	for (int i = 0; i < filas; ++i) {
		for (int j = 0; j < columnas; ++j) {
			if (!estacionamiento[i][j]) { // Espacio libre
				estacionamiento[i][j] = carro;
				stringstream s;
				s << "Plantel " << identificador << i << j;
				carro->setUbicacion(s.str());
				return true;
			}
		}
	}
	return false; // No hay espacio disponible
}

bool Plantel::eliminarCarro(int f, int c) {
	if (f < 0 || f >= filas || c < 0 || c >= columnas) return false;
	if (!estacionamiento[f][c]) return false; // No hay carro para eliminar
	delete estacionamiento[f][c];
	estacionamiento[f][c] = nullptr;
	return true;
}

bool Plantel::eliminarCarro(string placa)
{
	for (int i = 0; i < filas; ++i) {
		for (int j = 0; j < columnas; ++j) {
			if (estacionamiento[i][j] && estacionamiento[i][j]->getPlaca() == placa) {
				delete estacionamiento[i][j];
				estacionamiento[i][j] = nullptr;
				return true;
			}
		}
	}
	return false;
}

bool Plantel::desvincularCarro(string placa)
{
	for (int i = 0; i < filas; ++i) {
		for (int j = 0; j < columnas; ++j) {
			if (estacionamiento[i][j] && estacionamiento[i][j]->getPlaca() == placa) {
				estacionamiento[i][j] = nullptr;
				return true;
			}
		}
	}
	return false;
}



bool Plantel::estaVacio()
{
	return getCanDisponibles() == getCanTotal(); // true si todos los espacios estan libres
}

bool Plantel::esPosicionValida(int x, int y)
{
	return !estacionamiento[x][y]; // true si la posicion esta libre
}

string Plantel::mostrarPlantel() {
	//muestra las opciones del plantel
	stringstream ss;
	ss<<"Plantel " << identificador << " (" << filas << "x" << columnas << "):\n"
		<< "---------------------------------------------------------\n"
		<< "1). Mostrar informacion del plantel\n"
		<< "---------------------------------------------------------\n"
		<< "2). Ver Carro especifico\n"
		<< "---------------------------------------------------------\n"
		<< "3). Agregar carro\n"
		<< "---------------------------------------------------------\n"
		<< "4). Eliminar carro\n"
		<< "---------------------------------------------------------\n"
		<< "5). Salir\n"
		<< "---------------------------------------------------------\n"
		<< "Seleccione una opcion: ";
	return ss.str();

}

// ver =0: Informacion completa del plantel, ver=1: solo espacios del estacionamiento
string Plantel::mostrarEstacionamiento(int ver) {
	//Version 1: Mostrar solo la matriz del estacionamiento, ademas si un carro no esta "Disponible" mostrar "*******" en lugar de la placa
	//Version 0: Mostrar informacion completa del plantel + matriz del estacionamiento

	stringstream ss;
	if (ver == 0) {
		ss << "---------------------------------------------------------\n"
			<< "Plantel " << identificador << " (" << filas << "x" << columnas << "):\n"
			<< "Total de espacios: " << getCanTotal() << "\n"
			<< "Espacios disponibles: " << getCanDisponibles() << "\n\n"
			<< "---------------------------------------------------------\n";

	}
	for (int i = 0; i < filas * 14 - 1; i++) ss << "-";
	ss << "\n";
	for (int i = 0; i < filas; ++i) {
		for (int j = 0; j < columnas; j++) {
			ss << "|---"<< getEspacioEstacionamiento(i,j) << "---| ";
		}
		ss << "\n";
		for (int j = 0; j < columnas; ++j) {
			if (estacionamiento[i][j]) {
				if (ver == 1) {
					if (estacionamiento[i][j]->getEstadoCarro() != "Disponible") {
						ss << "| ******* | "; // Carro no disponible
						continue;
					}
					ss << "| " << estacionamiento[i][j]->getPlaca() << " | "; // Mostrar placa del carro
				}
				else {
					ss << "| " << estacionamiento[i][j]->getPlaca() << " | "; // Mostrar placa del carro
				}
			} else {
				ss << "|  Libre  | "; // Espacio libre
			}
		}
		ss << "\n";
		for (int i = 0; i < filas * 14 - 1; i++) ss << "-";
		ss << "\n";
	}
	return ss.str();
}


string Plantel::posicionesRecomendadas()
{
	stringstream s;

	for (int i = 0; i < filas; ++i) {
		for (int j = 0; j < columnas; ++j) {
			if (estacionamiento[i][j] != nullptr) continue; // solo evaluar espacios libres

			int vecinosVacios = 0;
			int vecinosValidos = 0;

			for (int fi = i - 1; fi <= i + 1; ++fi) {
				for (int cj = j - 1; cj <= j + 1; ++cj) {
					if (fi == i && cj == j) continue; // excluir la celda actual
					if (fi >= 0 && fi < filas && cj >= 0 && cj < columnas) {
						++vecinosValidos;
						if (estacionamiento[fi][cj] == nullptr) {
							++vecinosVacios;
						}
					}
				}
			}

			// Recomendado si todos los vecinos validos estan libres
			if (vecinosValidos > 0 && vecinosVacios == vecinosValidos) {
				s << getEspacioEstacionamiento(i, j) << " ";
			}
		}
	}
	return s.str();
}

void Plantel::actualizarPrecioCarros(char cateoria)
{
	//revisa si la categoria es valida y actualiza el precio de todos los carros en el plantel con esa categoria
	if (cateoria != 'A' && cateoria != 'B' && cateoria != 'C' && cateoria != 'D') return;
	for (int i = 0; i < filas; ++i) {
		for (int j = 0; j < columnas; ++j) {
			if (estacionamiento[i][j] && estacionamiento[i][j]->getCategoria() == cateoria) {
				estacionamiento[i][j]->actualizarPrecioDiario();
			}
		}
	}

}

// --- IMPLEMENTACION DE METODOS DE REPORTE ---

double Plantel::getPorcentajeOcupacion(){
	int total = getCanTotal();
	if (total == 0) return 0.0;
	int ocupados = total - getCanDisponibles();
	// Se usa 100.0 para asegurar la division de punto flotante
	return (static_cast<double>(ocupados) / total) * 100.0;
}

string Plantel::getDatosOcupacionStr(){
	stringstream ss;
	int total = getCanTotal();
	int ocupados = total - getCanDisponibles();

	double porcentaje = getPorcentajeOcupacion();

	// Implementacion basica para mostrar 2 decimales 
	// Multiplicar por 100, convertir a entero (trunca), y dividir para obtener partes.
	long long temp = (long long)(porcentaje * 100);
	long long parteEntera = temp / 100;
	long long parteDecimal = temp % 100;
	ss << "--------------------------------------------------------------\n";
	ss << "Plantel " << identificador << " (" << filas << "x" << columnas << "): ";
	ss << ocupados << " ocupados / " << total << " total ";
	ss << "-> " << parteEntera << ".";
	// Asegurar que el decimal tenga dos digitos (ej. 5.05 en lugar de 5.5)
	if (parteDecimal < 10) ss << "0";
	ss << parteDecimal << "% de Ocupacion";
	ss << "--------------------------------------------------------------\n";

	return ss.str();
}
