#include "Tokenizador.h"
#include "LectorArchivos.h"
#include "../sintactico/NotificadorError.h"

#include <cctype>
#include <cstdio>

#include <map>
#include <algorithm>
#include <string>
#include <cstring>
#include <iostream>

using namespace lexicoGrafico;
using namespace std;

Tokenizador::Tokenizador(char* nombreArchivo,bool ingles)
	:lectorArchivos(nombreArchivo),lexico(ingles)
{
	caracterObtenido = ' ';
	modoComentario = false;
	try
	{
		cadenaActual = new char[Globales::maximoTamanhoCadena + 1];
		lexema = new char[Globales::maximoTamanhoIdentificador + 1];
		lexemaActual = new char[Globales::maximoTamanhoIdentificador + 1];
	}
	catch(std::exception e)
	{
		printf("ERROR -- No se puede reservar memoria\n");
		exit(-1);
	}
	tokenAnterior = Lexico::nulo;
}


Tokenizador::~Tokenizador()
{
	delete[] cadenaActual;
	delete[] lexema;
	delete[] lexemaActual;
}

void Tokenizador::obtenerPrimerCaracter()
{
	while(caracterObtenido == ' ' || caracterObtenido == '\n' ||
		  caracterObtenido == '\t'
		)
		caracterObtenido = lectorArchivos.obtenerCaracter();
}

void Tokenizador::procesarPalabras()
{
		lexema[0] = caracterObtenido;
		indiceLexema = 1;
		while(isalpha(caracterObtenido = lectorArchivos.obtenerCaracter()) || isdigit(caracterObtenido))
		{
			if(indiceLexema < Globales::maximoTamanhoIdentificador)
				lexema[indiceLexema++] = caracterObtenido;
		}
		lexema[indiceLexema] = '\0';

		//es identificador o palabra reservada?
		std::map<std::string,Lexico::Token>::iterator iteradorDeBusqueda;

		iteradorDeBusqueda = lexico.mapaPalabrasReservadas.find(lexema);
		if(iteradorDeBusqueda != lexico.mapaPalabrasReservadas.end())
		{//Es palabra reservada
			tokenAnterior = tokenActual;
			tokenActual = (*iteradorDeBusqueda).second;
		}
		else
		{//No es palabra reservada
			tokenAnterior = tokenActual;
			tokenActual = Lexico::identificador;
		}
		strcpy(lexemaActual,lexema);
}

void Tokenizador::procesarNumeros(int signo)
{
	lexema[0] = caracterObtenido;
	indiceLexema = 1;
	int contadorDigitos = 1;
	bool puntoEncontrado = false;
	while(isdigit(caracterObtenido = lectorArchivos.obtenerCaracter()) || caracterObtenido == '.')
	{
		if(caracterObtenido == '.')
		{
			if(puntoEncontrado)
				break;
			else
				puntoEncontrado = true;
		}
		if(indiceLexema < Globales::maximoNumeroDigitos)
		{
			lexema[indiceLexema++] = caracterObtenido;
		}
		contadorDigitos++;
	}
	if(contadorDigitos > Globales::maximoNumeroDigitos)
	{
		sintactico::NotificadorError e;
		e.mostrarError(lectorArchivos.getLineaActual(),30);
		exit(1);
	}

	lexema[indiceLexema] = '\0';
	if(memchr(lexema,'.',strlen(lexema)) != NULL)
	{
		valorDecimal = atol(lexema);
		tokenAnterior = tokenActual;
		tokenActual = Lexico::numeroReal;
	}
	else
	{
		valorEntero = atoi(lexema);
		tokenAnterior = tokenActual;
		tokenActual = Lexico::numeroEntero;
	}
}


void Tokenizador::procesarCaracterEspecialComplejo()
{
			//primero lo vamos a buscar en el mapa a ver con cual simbolo comienza
			std::map<char,std::vector<std::string>>::iterator iteradorDeBusqueda;
			iteradorDeBusqueda = lexico.simbolosEspecialesComplejos.find(caracterObtenido);

			if(iteradorDeBusqueda != lexico.simbolosEspecialesComplejos.end())
			{//luego buscamos a ver si los simbolos que le siguen al inicial forman parte del simbolo
				//construimos un simbolo de dos caracteres
				char arregloDeBusqueda[3];
				arregloDeBusqueda[0] = caracterObtenido;
				caracterObtenido = lectorArchivos.obtenerCaracter(); // este es el look-ahead
				arregloDeBusqueda[1] = caracterObtenido;
				arregloDeBusqueda[2] = '\0';

				//y vamos a buscarlo en el vector de los simbolos que podrian ser validos
				std::vector<std::string> vectorDeSimbolos =  (*iteradorDeBusqueda).second;
				bool coincidenciaEncontrada = false;

				for(vector<string>::iterator it = vectorDeSimbolos.begin();it != vectorDeSimbolos.end();it++)
				{
					if(*it == arregloDeBusqueda)
					{
						coincidenciaEncontrada = true;

						//buscamos los casos especiales que estan formados por tres simbolos
						//if(strcmp(arregloDeBusqueda,"<=") == 0  || strcmp(arregloDeBusqueda,">=") == 0  || strcmp(arregloDeBusqueda,"<>") == 0 )
						//{
						//	caracterObtenido = lectorArchivos.obtenerCaracter();//usamos un segundo look-ahead
						//	if(caracterObtenido == '.')
						//	{
						//		char operadorLongitud3[4];
						//		operadorLongitud3[0] = arregloDeBusqueda[0];
						//		operadorLongitud3[1] = arregloDeBusqueda[1];
						//		operadorLongitud3[2] = '.';
						//		operadorLongitud3[3] = '\0';

						//		tokenActual = lexico.mapaSimbolosEspeciales[operadorLongitud3];
						//		caracterObtenido = lectorArchivos.obtenerCaracter();
						//		break;
						//	}
						//}
						//si no es un caso especial se usa simplemente el simbolo de tamanho dos
						tokenAnterior = tokenActual;
						tokenActual = lexico.mapaSimbolosEspeciales[arregloDeBusqueda];
						caracterObtenido = lectorArchivos.obtenerCaracter();
						break;
					}
				}
				if(!coincidenciaEncontrada) //si no hay coincidencia
				{
					arregloDeBusqueda[1] = '\0';
					tokenAnterior = tokenActual;
					tokenActual = lexico.mapaSimbolosEspeciales[arregloDeBusqueda];
				}
			}
			else
			{//si no esta en ningun pero ningun lado entonces es nulo
				tokenAnterior = tokenActual;
				tokenActual = lexico.nulo;
				caracterObtenido = lectorArchivos.obtenerCaracter();
			}
}
void Tokenizador::procesarCaracteresEspeciales()
{
		std::list<char>::iterator iteradorDeBusqueda;
		iteradorDeBusqueda = std::find(lexico.simbolosEspecialesTamanho1.begin(),
			lexico.simbolosEspecialesTamanho1.end(),caracterObtenido);

		if(iteradorDeBusqueda != lexico.simbolosEspecialesTamanho1.end())
		{//Es un simbolo especial simple la conversion es inmediata
			std::string stringBusqueda;
			stringBusqueda.push_back(caracterObtenido);
			tokenAnterior = tokenActual;
			tokenActual = lexico.mapaSimbolosEspeciales[stringBusqueda];
			caracterObtenido = lectorArchivos.obtenerCaracter();
		}
		else
		{//Es un simbolo especial de los complicados
			procesarCaracterEspecialComplejo();
		}
}

void Tokenizador::obtenerToken()
{
	obtenerPrimerCaracter();
	if(caracterObtenido < 0)
		caracterObtenido = '~';

	//printf("Analizando caracter %c\n",caracterObtenido);
	if(!modoComentario)
	{
		//si comienza con letra es identificador o palabra reservada
		if(isalpha(caracterObtenido))
		{
			procesarPalabras();
		}
		else if(isdigit(caracterObtenido))
		{//es un numero
			procesarNumeros();
		}
		else//caracteres especiales
		{
			procesarCaracteresEspeciales();
		}
		//comillas
		if(tokenActual == Lexico::comillasTok)
		{
			int indiceCadena = 0;
			while((caracterObtenido = lectorArchivos.obtenerCaracter()) != '\"')
			{
				if(indiceCadena < Globales::maximoTamanhoCadena)
					cadenaActual[indiceCadena++];
			}
			cadenaActual[indiceCadena] = '\0';
			tokenAnterior = tokenActual;
			tokenActual = Lexico::cadenaTok;
			caracterObtenido = lectorArchivos.obtenerCaracter();
		}

		esInicioDeComentario();
	}
	else
	{//Leemos todo lo que se pueda leer hasta encontrar *)
		while(true)
		{
			if(caracterObtenido == '}')
			{
					caracterObtenido = lectorArchivos.obtenerCaracter();
					modoComentario = false;
					tokenAnterior = tokenActual;
					tokenActual = Lexico::nulo;
					obtenerToken();
					break;
			}
			else
			{
				caracterObtenido = lectorArchivos.obtenerCaracter();
			}
			if(lectorArchivos.finDeArchivo)
			{
				sintactico::NotificadorError e;
				e.mostrarError(lectorArchivos.getLineaActual(),25);
			}
		}
	}

}

void Tokenizador::esInicioDeComentario()
{
	if(tokenActual == Lexico::llaveInicioTok)
	{
		modoComentario = true;
		caracterObtenido = lectorArchivos.obtenerCaracter();
		obtenerToken();
	}
	#ifdef MODO_DEBUG
		else
			cout << lexico.mapaPalabrasReservadasInverso[tokenActual] << " ";
	#endif
}


Lexico::Token Tokenizador::getTokenActual()
{
	return tokenActual;
}