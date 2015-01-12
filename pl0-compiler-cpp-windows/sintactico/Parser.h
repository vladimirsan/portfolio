#ifndef PARSER_H
#define PARSER_H

#include "../lexicoGrafico/Tokenizador.h"
#include "NotificadorError.h"
#include "TablaDeSimbolos.h"

namespace sintactico
{

	class Parser
	{
		private:
			lexicoGrafico::Tokenizador* tokenizador;
			NotificadorError notificadorError;
			TablaDeSimbolos tablaDeSimbolos;

			void declaracionConst();
			void declaracionVar();
			void instruccion();
			void condicion();
			void expresion();
			void termino();
			void factor();
			

			void assign();
			void operacionesArchivo();
			void operacionesTrigonometricas();
			void www();
			void write();
			void read();

		public:
			void bloque();
			
			Parser(lexicoGrafico::Tokenizador* pTokenizador,bool idioma);
	};
}

#endif