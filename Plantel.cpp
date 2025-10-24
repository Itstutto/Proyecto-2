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
bool Plantel::agregarCarro(Carro* carro, int pos) {

	int f = pos / 10;
	int c = pos % 10;

	if (f < 0 || f >= filas || c < 0 || c >= columnas) return false;

	if (f < 0 || f >= filas || c < 0 || c >= columnas) return false;
	if (estacionamiento[f][c]) return false; // Ya hay un carro
	estacionamiento[f][c] = carro;
	carro->setUbicacion(getEspacioEstacionamiento(f, c));
	return true;
}

bool Plantel::eliminarCarro(int f, int c) {
	if (f < 0 || f >= filas || c < 0 || c >= columnas) return false;
	if (!estacionamiento[f][c]) return false; // No hay carro para eliminar
	delete estacionamiento[f][c];
	estacionamiento[f][c] = nullptr;
	return true;
}

// ver =0: Informacion completa del plantel, ver=1: solo espacios del estacionamiento
string Plantel::mostrarEstacionamiento(int ver) {
	stringstream ss;
	if (ver == 0) {
		ss << "Plantel " << identificador << " (" << filas << "x" << columnas << "):\n"
			<< "Total de espacios: " << getCanTotal() << "\n"
			<< "Espacios disponibles: " << getCanDisponibles() << "\n\n";

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
				ss << "| " << estacionamiento[i][j]->getPlaca() << " | "; // Mostrar placa del carro
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

			// Recomendado si todos los vecinos válidos están libres
			if (vecinosValidos > 0 && vecinosVacios == vecinosValidos) {
				s << getEspacioEstacionamiento(i, j) << " ";
			}
		}
	}
	return s.str();
}
