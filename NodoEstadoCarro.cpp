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
string NodoEstadoCarro::getEstado(){
	return estado;
}
NodoEstadoCarro* NodoEstadoCarro::getSig(){
	return sig;
}
void NodoEstadoCarro::setEstado(string e){
	estado = e;
}
void NodoEstadoCarro::setSig(NodoEstadoCarro* s){
	sig = s;
}

