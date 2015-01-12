#ifndef TOKENIZADOR_H
#define TOKENIZADOR_H

#include "LectorArchivos.h"
#include "Lexico.h"
#include "Globales.h"


namespace lexicoGrafico
{
	class Tokenizador
	{
	private:
		LectorArchivos lectorArchivos;
		Lexico lexico;

		char* lexema;
		char* lexemaActual;
		char* cadenaActual;
		char caracterObtenido;
		int indiceLexema;
		Lexico::Token tokenActual;
		Lexico::Token tokenAnterior;

		int valorEntero;
		double valorDecimal;
		bool modoComentario;

		inline void obtenerPrimerCaracter();
		inline void procesarPalabras();
		inline void procesarNumeros(int signo = 1);
		inline void procesarCaracteresEspeciales();
		inline void procesarCaracterEspecialComplejo();

		inline void esInicioDeComentario();

	public:
		Tokenizador(char* nombreArchivo,bool ingles);
		~Tokenizador();
		void obtenerToken();
		Lexico::Token getTokenActual();
		Lexico::Token getTokenAnterior() { return tokenAnterior; }
		char* getLexemaActual(){ return lexemaActual; }
		int getLineaActual() { return lectorArchivos.getLineaActual(); }
	};
}
#endif