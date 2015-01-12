#ifndef LEXICO_H 
#define LEXICO_H

#include <map>
#include <string>
#include <list>
#include <vector>

namespace lexicoGrafico
{
	class Lexico
	{
	public:
		typedef enum Token
		{
			//Extra
			nulo,identificador,numeroEntero,numeroReal,
			//Palabras Reservadas
			beginTok, callTok, constTok, doTok,
			endTok, ifTok, oddTok, procedureTok, thenTok,
			varTok, whileTok,
			//Nuevas Palabras
			tipoIntTok,tipoRealTok,tipoFileTok,
			caseTok,ofTok,cadenaTok,
			readTok,readLnTok,writeTok,writeLnTok,wwwTok,sinTok,cosTok,tanTok,atanTok,asinTok,acosTok,
			assignTok,resetTok,closeTok,displayTok,
			//Simbolos especiales de 1
			menorTok,mayorTok,masTok,menosTok,porTok,entreTok,
			parentesisAbiertoTok,parentesisCerradoTok,igualTok,
			puntoTok,comaTok,puntoYcomaTok,
			//simbolos agregados
			llaveInicioTok,dosPuntosTok,comillasTok,
			//Simbolos especiales de 2
			menorIgualTok,diferenteTok,mayorIgualTok,asignacionTok
			// Simbolos especiales de 3
			//menorIgualPuntoTok,menorMayorPuntoTok,mayorIgualPuntoTok     
		}Token;

		std::map<std::string,Token> mapaPalabrasReservadas;
		std::map<Token,std::string> mapaPalabrasReservadasInverso;

		std::map<std::string,Token> mapaSimbolosEspeciales;

		std::list<char> simbolosEspecialesTamanho1;
		std::map<char,std::vector<std::string>> simbolosEspecialesComplejos;

	private:
		void llenarMapaPalabrasReservadas();
		void llenarMapaPalabrasReservadasEspanhol();
		void llenarMapaSimbolosEspeciales();
		void llenarListaSimbolosEspecialesTamanho1();
		void llenarMapaSimbolosEspecialesComplejos();
	public:
		Lexico(bool ingles = true);
	};
}
#endif
