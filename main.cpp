#include <iostream>
#include "Plantel.h"
#include "Carro.h"
using namespace std;

int main() {
	
	Plantel* plantel= new Plantel('A', 7, 8);

	Carro* carro1 = new Carro("123-ABC", "Corolla", "Toyota", "Madrid", "B1", 'B');
	Carro* carro2 = new Carro("567-DEF", "Civic", "Honda", "Barcelona", "B1", 'B');
	Carro* carro3 = new Carro("901-GHI", "Model S", "Tesla", "Valencia", "B2", 'A');
	Carro* carro4 = new Carro("345-JKL", "F-150", "Ford", "Sevilla", "C1", 'C');
	Carro* carro5 = new Carro("789-MNO", "Tucson", "Hyundai", "Bilbao", "B2", 'B');
	Carro* carro6 = new Carro("234-PQR", "Golf", "Volkswagen", "Granada", "B1", 'B');;




	cout<<plantel->agregarCarro(carro1, 0);
	cout << plantel->agregarCarro(carro2, 12);
	cout << plantel->agregarCarro(carro3, 24);
	cout << plantel->agregarCarro(carro4, 31);
	cout << plantel->agregarCarro(carro5, 43);
	cout << plantel->agregarCarro(carro6, 55);
	cout << plantel->mostrarEstacionamiento(0) << endl;

	int estado = 0;
	do {
		cout<< "Seleccione el estado del carro (estado actual: "<<carro1->getEstadoCarro()<<"):\n";
		cout << "1. Disponible\n";
		cout << "2. Alquilado\n";
		cout << "3. Devuelto\n";
		cout << "4. Revisión\n";
		cout << "5. Lavado\n";
		cout << "Ingrese el número correspondiente al estado: ";
		cin >> estado;
		if (estado > 6 || estado<1) {
			cout << "Estado inválido. Intente de nuevo.\n";
		}
		else
		{
			if (estado == 6) {}
			else {
				int comprobacion = carro1->setEstadosCarro(estado);
				if (comprobacion == 1)
				{
					cout << "Estado cambiado correctamente";
				}
				else if (comprobacion == -1) {
					cout << "No se puede cambiar al estado seleccionado desde el estado actual.\n";
				}
				else if (comprobacion == -2) {
					cout << "El carro ya está en el estado seleccionado.\n";
				}
				else {
					cout << "Opción inválida. Intente de nuevo.\n";
				}
			}
		}

	} while (estado!=6);


	cout << carro1->toString() << endl;

	cin.get();

	delete plantel;
	return 0;
}