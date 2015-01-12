#include "TablaDeSimbolos.h"
#include "../lexicoGrafico/Globales.h"
#include <cstring>
#include <stdexcept>
#include <cstdio>
#include <cstdlib>

using namespace sintactico;


TablaDeSimbolos::TablaDeSimbolos():
tablaDeSimbolos()
{
	indice = 0;
	try
	{
		tablaDeSimbolos.reserve(100);
	
		Simbolo temporal;
		tablaDeSimbolos.push_back(temporal);
	}
	catch(std::exception e)
	{
		printf("ERROR -- No se puede reservar memoria\n");
		exit(-1);
	}
}


TablaDeSimbolos::~TablaDeSimbolos()
{
	for(int i=0; i < tablaDeSimbolos.size(); i++)
   {
	   delete[] tablaDeSimbolos[i].nombre;
   }
}
void TablaDeSimbolos::insertar(Simbolo::TipoSimbolo tipo,char* nombre,bool controlCreacion,int indiceTablaDeSimbolo)
{
	Simbolo simboloInsertar;
	simboloInsertar.tipo = tipo;
	simboloInsertar.indiceTablaDeSimbolo = indiceTablaDeSimbolo;
	simboloInsertar.variableControlCreacion = controlCreacion;
	strcpy(simboloInsertar.nombre,nombre);

	indice++;
	if(indice >= tablaDeSimbolos.size())
	{
		try
		{
			tablaDeSimbolos.push_back(simboloInsertar);
		}
		catch(std::exception e)
		{
			printf("ERROR -- No se puede reservar memoria\n");
			exit(-1);
		}
	}
	else
	{
		tablaDeSimbolos[indice] = simboloInsertar;
	}
}

int TablaDeSimbolos::buscar(char* lexema)
{
	int i;
	strcpy(tablaDeSimbolos[0].nombre,lexema);
	i = indice;

	while((strcmp(tablaDeSimbolos[i].nombre,lexema)) != 0)
		i--;

	return i;
}

void TablaDeSimbolos::rellenarTiposTemporales(Simbolo::TipoSimbolo tipo)
{
	for(std::vector<Simbolo>::iterator i = tablaDeSimbolos.begin();
		i != tablaDeSimbolos.end();
		i++)
	{
		if(i->tipo == Simbolo::TipoSimbolo::VariableTemporal)
			i->tipo = tipo;
	}
}

bool TablaDeSimbolos::buscarRepetidos()
{
	for(std::vector<Simbolo>::iterator i = tablaDeSimbolos.begin();
		i != tablaDeSimbolos.end();
		i++)
	{
		if(i->tipo == Simbolo::TipoSimbolo::VariableTemporal)
		{
			if(contarOcurrencias(i->nombre) == true)
				return true;
		}

	}
	return false;
}

void TablaDeSimbolos::limpiarVariebleControlCreacion()
{
	for(std::vector<Simbolo>::iterator i = tablaDeSimbolos.begin();
		i != tablaDeSimbolos.end();
		i++)
	{
		i->variableControlCreacion = false;

	}
}

bool TablaDeSimbolos::buscarRepetidosControlCreacion()
{
	for(std::vector<Simbolo>::iterator i = tablaDeSimbolos.begin();
		i != tablaDeSimbolos.end();
		i++)
	{
		if(i->variableControlCreacion == true)
		{
			if(contarOcurrenciasControlCreacion(i->nombre) == true)
				return true;
		}

	}
	return false;
}

bool TablaDeSimbolos::buscarRepetidosProcedimientos(int indice)
{
	for(std::vector<Simbolo>::iterator i = tablaDeSimbolos.begin();
		i != tablaDeSimbolos.end();
		i++)
	{
		if(i->tipo == Simbolo::Procedimiento && i->indiceTablaDeSimbolo== indice)
		{
			if(contarOcurrenciasProcedimiento(i->nombre,indice) == true)
				return true;
		}

	}
	return false;
}

bool TablaDeSimbolos::contarOcurrencias(char* nombre)
{
	int contador = 0;
	std::vector<Simbolo>::iterator i = tablaDeSimbolos.begin();
	i++;
	for(;
		i != tablaDeSimbolos.end();
		i++)
	{
		if(i->tipo == Simbolo::TipoSimbolo::VariableTemporal &&  strcmp(nombre,i->nombre) == 0 )
		{
			contador++;
			if(contador > 1)
				return true;
		}
	}
	return false;
}

bool TablaDeSimbolos::contarOcurrenciasControlCreacion(char* nombre)
{
	int contador = 0;
	std::vector<Simbolo>::iterator i = tablaDeSimbolos.begin();
	i++;
	for(;
		i != tablaDeSimbolos.end();
		i++)
	{
		if(i->variableControlCreacion == true &&  strcmp(nombre,i->nombre) == 0 )
		{
			contador++;
			if(contador > 1)
				return true;
		}
	}
	return false;
}

bool TablaDeSimbolos::contarOcurrenciasProcedimiento(char* nombre,int indice)
{
	int contador = 0;
	std::vector<Simbolo>::iterator i = tablaDeSimbolos.begin();
	i++;
	for(;
		i != tablaDeSimbolos.end();
		i++)
	{
		if(i->tipo == Simbolo::Procedimiento && i->indiceTablaDeSimbolo == indice  &&  strcmp(nombre,i->nombre) == 0 )
		{
			contador++;
			if(contador > 1)
				return true;
		}
	}
	return false;
}