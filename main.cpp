#include <iostream>
#include "Plantel.h"
#include "Carro.h"
using namespace std;

int main() {
	
	Plantel* plantel= new Plantel('A', 6, 7);

	Carro* carro1 = new Carro("123-ABC", "Corolla", "Toyota", "Madrid", "B1", 'B');
	Carro* carro2 = new Carro("567-DEF", "Civic", "Honda", "Barcelona", "B1", 'B');
	Carro* carro3 = new Carro("901-GHI", "Model S", "Tesla", "Valencia", "B2", 'A');
	Carro* carro4 = new Carro("345-JKL", "F-150", "Ford", "Sevilla", "C1", 'C');
	Carro* carro5 = new Carro("789-MNO", "Tucson", "Hyundai", "Bilbao", "B2", 'B');
	Carro* carro6 = new Carro("234-PQR", "Golf", "Volkswagen", "Granada", "B1", 'B');
	Carro* carro7 = new Carro("678-STU", "X5", "BMW", "Málaga", "B2", 'B');
	Carro* carro8 = new Carro("012-VWX", "A4", "Audi", "Zaragoza", "B1", 'B');
	Carro* carro9 = new Carro("456-YZA", "Master", "Renault", "Oviedo", "C2", 'C');
	Carro* carro10 = new Carro("890-BCD", "Kiger", "Renault", "Santander", "B1", 'B');




	plantel->agregarCarro(carro1, 0, 0);
	plantel->agregarCarro(carro2, 1, 2);
	plantel->agregarCarro(carro3, 2, 4);
	plantel->agregarCarro(carro4, 3, 1);
	plantel->agregarCarro(carro5, 4, 3);
	plantel->agregarCarro(carro6, 5, 5);
	cout << plantel->mostrarEstacionamiento(0) << endl;

	cout << carro1->toString() << endl;


	delete plantel;
	return 0;
}