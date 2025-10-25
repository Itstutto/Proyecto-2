#include "ContratoAlquiler.h"
#include <sstream>

string ContratoAlquiler::toString() const {
	stringstream ss;
	ss << "Contrato - " << toResumen();
	return ss.str();
}
