#ifndef TDS_H 
#define TDS_H 

#include "../lexicoGrafico/Globales.h"
#include "Simbolo.h"
#include <vector>

namespace sintactico
{
	class TablaDeSimbolos 
	{
		public:
			TablaDeSimbolos();

			bool buscarRepetidos();
			bool buscarRepetidosControlCreacion();
			bool buscarRepetidosProcedimientos(int indice);
			void insertar(Simbolo::TipoSimbolo tipo,char* nombre,bool controlCreacion,int indiceTablaDeSimbolo  = -1);
			void limpiarVariebleControlCreacion();
			int buscar(char* lexema);
			void rellenarTiposTemporales(Simbolo::TipoSimbolo tipo);

			int getIndice() { return indice;}
			void setIndice(int pIndice) { indice = pIndice;}

			Simbolo::TipoSimbolo getTipoDadoIndice(int i) { return tablaDeSimbolos[i].tipo; }	
			~TablaDeSimbolos();
		private:
			int indice;
			std::vector<Simbolo> tablaDeSimbolos;

			bool contarOcurrencias(char* nombre);
			bool contarOcurrenciasControlCreacion(char* nombre);
			bool contarOcurrenciasProcedimiento(char* nombre,int indice);
	};
}

#endif