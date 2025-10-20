#include "NodoPl.h"

NodoPl::NodoPl()
{
	dato = nullptr;
	sig = nullptr;
}

NodoPl::NodoPl(Plantel* p)
{
	dato = p;
	sig = nullptr;
}
