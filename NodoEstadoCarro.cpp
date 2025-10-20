#include "NodoEstadoCarro.h"

NodoEstadoCarro::NodoEstadoCarro(){
	estado = "";
	sig = nullptr;
}

NodoEstadoCarro::NodoEstadoCarro(string e)
{
	estado = e;
	sig = nullptr;
}
