#ifndef LECTOR_ARCHIVOS_H
#define LECTOR_ARCHIVOS_H

#define MODO_DEBUG

#include "Globales.h"

#include <cstdio>
#include <stdexcept>

namespace lexicoGrafico
{
	class LectorArchivos
	{
		private:
			char* bufferLinea;
			FILE* fp;

			int offsetBuffer;
			int tamanhoCadena;

			int getLine(char s[],int lim);
			void imprimirBuffer();
			int lineaActual;
		public:

			LectorArchivos(char* nombreArchivo);
			~LectorArchivos();
			char obtenerCaracter();
			bool finDeArchivo;
			int getLineaActual() { return lineaActual; }
	};
}

#endif