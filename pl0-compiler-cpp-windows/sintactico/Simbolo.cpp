#include "Simbolo.h"

#include <stdexcept>
#include <cstdio>

using namespace sintactico;
Simbolo::Simbolo()
{
	try
	{
		nombre = new char[lexicoGrafico::Globales::maximoTamanhoIdentificador + 1];
	}
	catch(std::exception e)
	{
		printf("ERROR -- No se puede reservar memoria\n");
		exit(-1);
	}
}

Simbolo::~Simbolo()
{
}