#ifndef NOTIFICADOR_ERROR_H
#define NOTIFICADOR_ERROR_H

namespace sintactico
{

	class NotificadorError
	{
		private:
		public:
			static bool ingles;
			void mostrarErrorIngles(int linea,int codigoError);
			void mostrarErrorEspanhol(int linea,int codigoError);
			void mostrarError(int linea,int codigoError);
	};
}

#endif