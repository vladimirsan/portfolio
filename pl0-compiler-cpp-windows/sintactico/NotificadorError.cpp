#include "NotificadorError.h"
#include <cstdio>
#include <cstdlib>

using namespace sintactico;

bool NotificadorError::ingles = true;

void NotificadorError::mostrarError(int linea,int codigoError)
{
	if(ingles)
		mostrarErrorIngles(linea,codigoError);
	else
		mostrarErrorEspanhol(linea,codigoError);
}

void NotificadorError::mostrarErrorIngles(int linea,int codigoError)
{
	char* mensajesDeError[] = {"",
	/*Error 1 */ "Use '=' instead of ': ='",
	/*Error 2 */ "Must be followed by a number",
	/*Error 3 */ "The identifier must be followed by '='",
	/*Error 4 */ "CONST, VAR and PROCEDURE must be followed by an identifier",
	/*Error 5 */ "Missing a comma or a semicolon",
	/*Error 6 */ "Incorrect symbol after a procedure declaration",
	/*Error 7 */ "Instruction was expected",
	/*Error 8 */ "Incorrect symbol behind the instructions of a block",
	/*Error 9 */ "Point is expected",
	/*Error 10*/ "Missing a semicolon between statements",
	/*Error 11*/ "Undeclared identifier",
	/*Error 12*/ "Assignments are not allowed to constant or procedures",
	/*Error 13*/ "Expected the assignment operator",
	/*Error 14*/ "CALL must be followed by an identifier",
	/*Error 15*/ "Makes no sense to call a constant or a variable",
	/*Error 16*/ "Expect a THEN",
	/*Error 17*/ "Expect a END or a semicolon",
	/*Error 18*/ "Expect a DO",
	/*Error 19*/ "An incorrect symbol follows an instruction",
	/*Error 20*/ "Expected a relational operator",
	/*Error 21*/ "An expression must not contain a process identifier",
	/*Error 22*/ "Missing a closing parenthesis",
	/*Error 23*/ "The last factor can not be followed by this symbol or missing a semicolon",
	/*Error 24*/ "An expression can not start with this symbol",
	/*Error 25*/ "A comment is incomplete",
	/*Error 26*/ "",
	/*Error 27*/ "",
	/*Error 28*/ "",
	/*Error 29*/ "",
	/*Error 30*/ "This number is too large - trunc (5)",
	/*Error 31*/ "Size is exceeded the Table of Symbols",
	/*Error 32*/ "The source program is incomplete",
	/*Error 33*/ "The source program is too long",
	/*Error 34*/ "Nesting too deep for Routines",
	/*Error 35*/ "Maximum is exceeded PL5 whole - it is assumed zero",
	/*Error 36 */"Expected: in the declaration of variables",//36
	/*Error 37 */"Type of data expected",//37
	/*Error 38 */"Expected open parenthesis",//38
	/*Error 39 */"Expecting a variable of type integer or real",//39
	/*Error 40 */"Expected a closing parenthesis",//40
	/*Error 41 */"Expecting a string",//41
	/*Error 42 */"Expected identifier",//42
	/*Error 43 */"Expected variable file type",//43
	/*Error 44 */"The keyword was expected OF",//44
	/*Error 45 */"An integer was expected",//45
	/*Error 46 */"Expected integer constant",//46
	/*Error 47 */"Expected ; or END",//47
	/*Error 48 */"Repeated symbols were found in the definition",//48
	/*Error 49 */"BEGIN expected"//48
	};

	printf("ERROR %d -- Line: %d -- %s\n",codigoError,linea,mensajesDeError[codigoError]);
	exit(-1);	
}

void NotificadorError::mostrarErrorEspanhol(int linea,int codigoError)
{
	char* mensajesDeError[] = {"",
	/*Error 1 */ "Usar ' = ' en vez de ' := ' ",
	/*Error 2 */ "Debe ir seguido de un número",
	/*Error 3 */ "El identificador debe ir seguido de ' = ' ",
	/*Error 4 */ "CONSTANTE, VARIABLE y PROCEDIMIENTO deben ir seguidos de un identificador",
	/*Error 5 */ "Falta una coma o un punto y coma",
	/*Error 6 */ "Símbolo incorrecto después de una declaración de procedimiento",
	/*Error 7 */ "Se esperaba una instrucción",
	/*Error 8 */ "Símbolo incorrecto detrás de las instrucciones de un bloque",
	/*Error 9 */ "Se espera un punto",
	/*Error 10*/ "Falta un punto y coma entre instrucciones",
	/*Error 11*/ "Identificador no declarado",
	/*Error 12*/ "No estan permitidas las asignaciones a constantes o procedimientos",
	/*Error 13*/ "Se esperaba el operador de asignación",
	/*Error 14*/ "LLAMAR debe de ir seguido de un identificador",
	/*Error 15*/ "No tiene sentido llamar a una constante o a una variable",
	/*Error 16*/ "Se espera un ENTONCES",
	/*Error 17*/ "Se espera un FIN o un punto y coma",
	/*Error 18*/ "Se espera un HACER",
	/*Error 19*/ "Un símbolo incorrecto sigue a una instrucción",
	/*Error 20*/ "Se esperaba un operador relacional",
	/*Error 21*/ "Una expresión no debe de contener un identificador de procedimiento",
	/*Error 22*/ "Falta un parentesis de cierre",
	/*Error 23*/ "El factor anterior no puede ir seguido de este símbolo o falta un punto y coma",
	/*Error 24*/ "Una expresión no puede empezar con este símbolo",
	/*Error 25*/ "Un comentario esta incompleto",
	/*Error 26*/ "",
	/*Error 27*/ "",
	/*Error 28*/ "",
	/*Error 29*/ "",
	/*Error 30*/ "Este número es demasiado grande - trunc(5)",
	/*Error 31*/ "Se rebaso el tamaño de la Tabla de Símbolos",
	/*Error 32*/ "El programa fuente esta incompleto",
	/*Error 33*/ "El programa fuente es demasiado largo",
	/*Error 34*/ "Anidamiento demasiado profundo para los procedimientos",
	/*Error 35*/ "Se rebasa el máximo entero de pl5--se asume cero",
	/*Error 36 */"Se esperaba : en la declaración de variables",//36
	/*Error 37 */"Se esperaba tipo de datos",//37
	/*Error 38 */"Se esperaba un parentesis abierto",//38
	/*Error 39 */"Se esperaba una variable de tipo entero o real",//39
	/*Error 40 */"Se esperaba un parentesis cerrado",//40
	/*Error 41 */"Se esperaba una cadena",//41
	/*Error 42 */"Se esperaba un identificador",//42
	/*Error 43 */"Se esperaba una variable tipo archivo",//43
	/*Error 44 */"Se esperaba la palabra reservada DE",//44
	/*Error 45 */"Se esperaba un entero",//45
	/*Error 46 */"Se esperaba una constante entera",//46
	/*Error 47 */"Se esperaba ; o FIN",//47
	/*Error 48 */"Se encontraron simbolos repetidas en la definición",//48
	/*Error 49 */"Se esperaba un begin"//48

	};

	printf("ERROR %d -- Linea: %d -- %s\n",codigoError,linea,mensajesDeError[codigoError]);
	exit(-1);	
	//llalalala
}