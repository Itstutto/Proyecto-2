#include <iostream>
#include "Sucursal.h"
#include "Menu.h"
using namespace std;

int main() {
	Sucursal* s = new Sucursal(1);
	Menu* m = new Menu(s);
	m->iniciar();
	delete m;
	delete s;
	return 0;
}