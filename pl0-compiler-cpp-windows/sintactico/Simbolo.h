#ifndef SIMBOLO_H 
#define SIMBOLO_H 

#include "../lexicoGrafico/Globales.h"

namespace sintactico
{
	class Simbolo
	{
		public:
			typedef enum
			{
				ConstanteEntera,ConstanteReal,VariableEntera,VariableTemporal,VariableReal,VariableArchivo,Procedimiento
			}TipoSimbolo;

			char* nombre;
			TipoSimbolo tipo;
			bool variableControlCreacion;
			int indiceTablaDeSimbolo;

			Simbolo();
			~Simbolo();
	};
}
#endif