#pragma once
#include "Plantel.h"
struct NodoPl
{
	Plantel* dato;
	NodoPl* sig;
	NodoPl();
	NodoPl(Plantel* p);
};

