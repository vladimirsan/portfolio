#include "LectorArchivos.h"
#include "../sintactico/NotificadorError.h"

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cctype>


using namespace lexicoGrafico;
using namespace std;

LectorArchivos::LectorArchivos(char* nombreArchivo)
{
	fp = NULL;
	fp = fopen(nombreArchivo,"r");

	if(fp == NULL)
		throw runtime_error("No se puede abrir el archivo proporcionado");

	finDeArchivo = false;

	offsetBuffer = -1; 
	tamanhoCadena = 0;
	lineaActual = 0;
	try
	{
		bufferLinea = new char[Globales::tamanhoBuffer];
	}
	catch(std::exception e)
	{
		printf("ERROR -- No se puede reservar memoria\n");
		exit(-1);
	}
}

LectorArchivos::~LectorArchivos()
{
	if(fp != NULL)
		fclose(fp);

	delete[] bufferLinea;
}


char LectorArchivos::obtenerCaracter()
{
	//procesando la salida del programa?
	if(finDeArchivo)
	{
		fclose(fp);
		sintactico::NotificadorError e;
		e.mostrarError(lineaActual,32);
	}

	//procesando la recarga del buffer
	if(offsetBuffer ==  tamanhoCadena - 1)
	{
		tamanhoCadena = getLine(bufferLinea,Globales::tamanhoBuffer);

		
		if(tamanhoCadena == 0)
			finDeArchivo = true;
		else
			imprimirBuffer();

		offsetBuffer = -1;
	}

	offsetBuffer++;

	//procesando los casos triviales
	if(bufferLinea[offsetBuffer] == '\0' || finDeArchivo == true)
		return ' ';
	else
		return tolower(bufferLinea[offsetBuffer]);
}

void LectorArchivos::imprimirBuffer()
{
	#ifdef MODO_DEBUG
		char test = bufferLinea[strlen(bufferLinea) -1];
		if(test != '\n')
			cout << endl << bufferLinea << endl << endl;
		else
			cout << endl <<bufferLinea << endl;
	#endif
}



int LectorArchivos::getLine(char s[],int lim)
{
	lineaActual++;
 int c,i;

 for (i=0;i<lim-1 && (c=getc(fp))!=EOF && c!='\n';++i)
     s[i]=c;

 if (c=='\n') 
 {
    s[i]=c;
    ++i;
 }

 s[i]='\0';
 return (i);
}