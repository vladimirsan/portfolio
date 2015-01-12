#include "lexicoGrafico\LectorArchivos.h"

#include <iostream>
#include <cstdio>
#include <stdexcept>

#include "lexicoGrafico\Tokenizador.h"
#include "sintactico\Parser.h"
#include "lexicoGrafico\Lexico.h"
#include "sintactico\NotificadorError.h"


using namespace std;
using namespace sintactico;
using namespace lexicoGrafico;

int main(int argc,char** argv)
{
	bool idioma;
	#ifndef MODO_DEBUG
	if(argc != 7)
	{
		printf("ERROR -- Numero erroneo de argumentos\n");
		printf("Uso Correcto: parser.exe idioma tamanhoBuffer tamanhoIdentificador tamanhoNumero tamanhoCadena nombre_de_archivo");
	    exit(-1);
	}
	idioma = (strcmp("e",argv[1]) == 0) ? true:false;
	Globales::tamanhoBuffer = atoi(argv[2]);
	Globales::maximoTamanhoIdentificador = atoi(argv[3]);
	Globales::maximoNumeroDigitos = atoi(argv[4]);
	Globales::maximoTamanhoCadena = atoi(argv[5]);
	#else
		idioma = true;
	#endif


	try
	{
		#ifndef MODO_DEBUG
		lexicoGrafico::Tokenizador tokenizador(argv[6],idioma);
		#else
		lexicoGrafico::Tokenizador tokenizador("C:/aoeu.txt",idioma);
		#endif
		Parser parser(&tokenizador,idioma);

		tokenizador.obtenerToken();
		parser.bloque();

		if(tokenizador.getTokenActual() != Lexico::puntoTok)
		{
			NotificadorError notificadorError;
			notificadorError.mostrarError(tokenizador.getLineaActual(),9);
		}
		//falta incluir las estadisticas!
		if(idioma)
			printf("0 errors detected\n");
		else
			printf("0 errores detectados\n");
	}
	catch(std::exception e)
	{
		printf("ERROR -- No se puede abrir el archivo %s",argv[6]);
		exit(-1);
	}
}