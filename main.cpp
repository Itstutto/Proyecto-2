#include <iostream>
#include "Sucursal.h"
#include "Menu.h"
using namespace std;

int main() {
	
	Menu* m = new Menu();
	m->iniciar();
	delete m;
	return 0;
}