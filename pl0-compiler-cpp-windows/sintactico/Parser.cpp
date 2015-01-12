#include "Parser.h"


using namespace sintactico;
using namespace lexicoGrafico;

sintactico::Parser::Parser(lexicoGrafico::Tokenizador* pTokenizador,bool idioma):
notificadorError(),tablaDeSimbolos()
{
	NotificadorError::ingles = idioma;
	tokenizador = pTokenizador;
}

void Parser::bloque()
{
	static int contadorRecursion = 1;
	 int temp;
 
	 if (tokenizador->getTokenActual() == Lexico::constTok) 
	 {
		tokenizador->obtenerToken();
		declaracionConst();
		while (tokenizador->getTokenActual()==Lexico::comaTok) 
		{
			tokenizador->obtenerToken();
			declaracionConst();
		}
		if (tokenizador->getTokenActual()==Lexico::puntoYcomaTok) 
			tokenizador->obtenerToken();
		else
			notificadorError.mostrarError(tokenizador->getLineaActual(),5); //error 5: falta una coma o un punto y coma
	}

	bool puntoYcomaEncontrada = false;
	if (tokenizador->getTokenActual()==Lexico::varTok) 
	{
		tokenizador->obtenerToken();
		declaracionVar(); 
		while (tokenizador->getTokenActual()==Lexico::puntoYcomaTok) 
		{
			tokenizador->obtenerToken();

			if(tokenizador->getTokenActual() == Lexico::identificador)
			{
				puntoYcomaEncontrada = false;
				declaracionVar();
			}
			else
			{
				puntoYcomaEncontrada = true;
				//if(tokenizador->getTokenActual() == Lexico::puntoYcomaTok)
				break;
			}
		}
		//if (tokenizador->getTokenActual()==Lexico::puntoYcomaTok)
		if(!puntoYcomaEncontrada)
			notificadorError.mostrarError(tokenizador->getLineaActual(),5); //error 5: Falta una coma o un punto y coma

		if(tablaDeSimbolos.buscarRepetidosControlCreacion() == true)
			notificadorError.mostrarError(tokenizador->getLineaActual(),48);
		tablaDeSimbolos.limpiarVariebleControlCreacion();
	}
  
	while (tokenizador->getTokenActual()==Lexico::procedureTok) 
	{
		tokenizador->obtenerToken();
		if (tokenizador->getTokenActual()==Lexico::identificador) 
		{
			tablaDeSimbolos.insertar(Simbolo::Procedimiento,tokenizador->getLexemaActual(),true,contadorRecursion);
			if(tablaDeSimbolos.buscarRepetidosProcedimientos(contadorRecursion) == true)
				notificadorError.mostrarError(tokenizador->getLineaActual(),48);

			tokenizador->obtenerToken();
		}
		else
			notificadorError.mostrarError(tokenizador->getLineaActual(),4); //error 4: Const, Var y Procedure deben ir seguidos de un identificador

		if (tokenizador->getTokenActual()==Lexico::puntoYcomaTok)
			tokenizador->obtenerToken();
		else
			notificadorError.mostrarError(tokenizador->getLineaActual(),5); //error 5: falta una coma o un punto y coma
		temp = tablaDeSimbolos.getIndice();
		contadorRecursion++;
		bloque();       
		contadorRecursion--;
		tablaDeSimbolos.setIndice(temp);
         
       if (tokenizador->getTokenActual()==Lexico::puntoYcomaTok)
	      tokenizador->obtenerToken();
	   else 
	      notificadorError.mostrarError(tokenizador->getLineaActual(),5);


	}

	if(tokenizador->getTokenActual() == Lexico::beginTok)
	{
		tokenizador->obtenerToken();
		instruccion();
		 while (tokenizador->getTokenActual()==Lexico::puntoYcomaTok) 
		 {
			   tokenizador->obtenerToken();
			   instruccion();
		 }
		 if (tokenizador->getTokenActual()==Lexico::endTok)
			tokenizador->obtenerToken();
		 else
			notificadorError.mostrarError(tokenizador->getLineaActual(),17); //error 17: Se esperaba un "END" o un punto y coma 
	}
	else
		notificadorError.mostrarError(tokenizador->getLineaActual(),49);//error 5: falta una coma o un punto y coma 
}

void Parser::declaracionConst()
{
	if (tokenizador->getTokenActual()==Lexico::identificador) 
	{
		tokenizador->obtenerToken();
		if (tokenizador->getTokenActual()==Lexico::igualTok) 
		{
			tokenizador->obtenerToken();
			if (tokenizador->getTokenActual()==Lexico::numeroEntero) 
			{
				tablaDeSimbolos.insertar(Simbolo::ConstanteEntera,tokenizador->getLexemaActual(),true);
				tokenizador->obtenerToken();
			}
			else if (tokenizador->getTokenActual()==Lexico::numeroReal) 
			{
				tablaDeSimbolos.insertar(Simbolo::ConstanteReal,tokenizador->getLexemaActual(),true);
				tokenizador->obtenerToken();
			}
			else
				notificadorError.mostrarError(tokenizador->getLineaActual(),2) ; //error 2: debe ir seguido de un número
		}
		else
			notificadorError.mostrarError(tokenizador->getLineaActual(),3) ; //error 3: el identificador debe ir seguido de "=" 
	}
	else
		notificadorError.mostrarError(tokenizador->getLineaActual(),4) ; //error 4: Const, Var y Procedure deben ir seguidos de un identificador
}

void Parser::declaracionVar()
{
		do
		{
			if (tokenizador->getTokenActual()==Lexico::identificador) 
			{
				tablaDeSimbolos.insertar(Simbolo::VariableTemporal,tokenizador->getLexemaActual(),true);
				tokenizador->obtenerToken();
			}
			else
				notificadorError.mostrarError(tokenizador->getLineaActual(),4) ; //error 4: Const, Var y Procedure deben ir seguidos de un identificador

			if(tokenizador->getTokenActual() == Lexico::comaTok)
				tokenizador->obtenerToken();
			else
				break;
		}while(1);

		if(tokenizador->getTokenActual() == Lexico::dosPuntosTok)
		{
			if(tablaDeSimbolos.buscarRepetidos() == true)
				notificadorError.mostrarError(tokenizador->getLineaActual(),48);

			tokenizador->obtenerToken();
			if(tokenizador->getTokenActual() == Lexico::tipoIntTok || tokenizador->getTokenActual() == Lexico::tipoRealTok || tokenizador->getTokenActual() == Lexico::tipoFileTok)
			{
				if(tokenizador->getTokenActual() == Lexico::tipoIntTok)
					tablaDeSimbolos.rellenarTiposTemporales(Simbolo::VariableEntera);

				if(tokenizador->getTokenActual() == Lexico::tipoRealTok)
					tablaDeSimbolos.rellenarTiposTemporales(Simbolo::VariableReal);

				if(tokenizador->getTokenActual() == Lexico::tipoFileTok)
					tablaDeSimbolos.rellenarTiposTemporales(Simbolo::VariableArchivo);
				tokenizador->obtenerToken();
			}
			else
				notificadorError.mostrarError(tokenizador->getLineaActual(),37);// Se esperaba tipo de datos
		}
		else
			notificadorError.mostrarError(tokenizador->getLineaActual(),36);//Se esperaba : en la declaracion de variables
}

void Parser::instruccion()
{
	int i;
	if (tokenizador->getTokenActual()==Lexico::identificador) 
	{
		//ve a buscarlo a la tabla de símbolos
		i = tablaDeSimbolos.buscar(tokenizador->getLexemaActual());

		if (i==0)
			notificadorError.mostrarError(tokenizador->getLineaActual(),11); //error 11: identificador no declarado 
		else if(tablaDeSimbolos.getTipoDadoIndice(i) != Simbolo::VariableEntera && tablaDeSimbolos.getTipoDadoIndice(i) != Simbolo::VariableReal) 
			notificadorError.mostrarError(tokenizador->getLineaActual(),12); //error 12: no están permitidas las asignaciones a constantes o a procedimientos o a archivos

		tokenizador->obtenerToken();

		if (tokenizador->getTokenActual()==Lexico::asignacionTok)
			tokenizador->obtenerToken();
		else
			notificadorError.mostrarError(tokenizador->getLineaActual(),13) ; //error 13: se esperaba el operador de asignación 

		expresion();	   
	} 
	else
	{
		if (tokenizador->getTokenActual()==Lexico::callTok) 
		{
			tokenizador->obtenerToken();
			if (tokenizador->getTokenActual()!=Lexico::identificador)
				notificadorError.mostrarError(tokenizador->getLineaActual(),14); //error 14: "CALL" debe ir seguido de un identificador 
			else 
			{
				//buscar el nombre del procedimiento en la tabla de símbolos
				i = tablaDeSimbolos.buscar(tokenizador->getLexemaActual());
				if (i==0)
					notificadorError.mostrarError(tokenizador->getLineaActual(),11); //error 11: Identificador no declarado 
				else if(tablaDeSimbolos.getTipoDadoIndice(i) != Simbolo::Procedimiento)
					notificadorError.mostrarError(tokenizador->getLineaActual(),15); //error 15 : No tiene sentido llamar a una constante o a una variable 

				tokenizador->obtenerToken();
			}
		} 
		else if (tokenizador->getTokenActual()==Lexico::ifTok) 
		{
	      tokenizador->obtenerToken();
		  condicion();
		  if (tokenizador->getTokenActual()==Lexico::thenTok)
	         tokenizador->obtenerToken();
	      else
	         notificadorError.mostrarError(tokenizador->getLineaActual(),16); //error 16: Se esperaba un "THEN" 
		  instruccion();
       } 
	   else
	   {
	      if (tokenizador->getTokenActual()==Lexico::beginTok) 
		  {
	         tokenizador->obtenerToken();
			 instruccion();
			 while (tokenizador->getTokenActual()==Lexico::puntoYcomaTok) 
			 {
	               tokenizador->obtenerToken();
	               instruccion();
	         }
	         if (tokenizador->getTokenActual()==Lexico::endTok)
	            tokenizador->obtenerToken();
	         else
	            notificadorError.mostrarError(tokenizador->getLineaActual(),17); //error 17: Se esperaba un "END" o un punto y coma 
	      } 
		  else if (tokenizador->getTokenActual()==Lexico::whileTok) 
		  {
	           	tokenizador->obtenerToken();
				condicion();

				if (tokenizador->getTokenActual()==Lexico::doTok) 
	               tokenizador->obtenerToken();
	            else
	               notificadorError.mostrarError(tokenizador->getLineaActual(),18); //error 18: Se esperaba un "DO" 
				instruccion();
		  }
		  else if(tokenizador->getTokenActual() == Lexico::caseTok)
		  {
	           	tokenizador->obtenerToken();
				expresion();
				if (tokenizador->getTokenActual()==Lexico::ofTok)
				{
					tokenizador->obtenerToken();
					
					if (tokenizador->getTokenActual() != Lexico::endTok)
					{
						bool constanteOk = false;
						do
						{
							do//Este do es el de las , en las constantes
							{
								constanteOk = false;
	
								if (tokenizador->getTokenActual() == Lexico::numeroEntero)
								{
									constanteOk = true;
								}
								if (tokenizador->getTokenActual() == Lexico::identificador)
								{
									i = tablaDeSimbolos.buscar(tokenizador->getLexemaActual());
									if (i==0)
										notificadorError.mostrarError(tokenizador->getLineaActual(),11); //error 11: Identificador no declarado 
									else if(tablaDeSimbolos.getTipoDadoIndice(i) == Simbolo::ConstanteEntera)
										constanteOk = true;
								}
								if(!constanteOk)
									notificadorError.mostrarError(tokenizador->getLineaActual(),46);
								else
								{
									tokenizador->obtenerToken();
									if (tokenizador->getTokenActual()!=Lexico::comaTok)
									{
										break;
									}
									else
										tokenizador->obtenerToken();
								}
							}while(1);
							if (tokenizador->getTokenActual()!=Lexico::dosPuntosTok)
								notificadorError.mostrarError(tokenizador->getLineaActual(),36);
							else
							{
								tokenizador->obtenerToken();
								instruccion();

								if (tokenizador->getTokenActual()==Lexico::puntoYcomaTok)
								{
									tokenizador->obtenerToken();
								}
								else if (tokenizador->getTokenActual()==Lexico::endTok)
								{
									tokenizador->obtenerToken();
									break;
								}
								else
								{
									notificadorError.mostrarError(tokenizador->getLineaActual(),47);
								}

							}
						}while(1);//mega end ; loop
					}
				}
				else
	               notificadorError.mostrarError(tokenizador->getLineaActual(),44); //error 18: Se esperaba un of
		  }
		  else if(tokenizador->getTokenActual() == Lexico::readTok || tokenizador->getTokenActual() == Lexico::readLnTok)
		  {
			  read();
		  }
		  else if(tokenizador->getTokenActual() == Lexico::writeTok || tokenizador->getTokenActual() == Lexico::writeLnTok)
		  {
			  write();
			}
			else if(tokenizador->getTokenActual() == Lexico::wwwTok) 
			{
				www();
			}
			else if(tokenizador->getTokenActual() == Lexico::assignTok) 
			{
				assign();
			}
			else if(tokenizador->getTokenActual() == Lexico::resetTok || tokenizador->getTokenActual() == Lexico::closeTok || tokenizador->getTokenActual() == Lexico::displayTok)
			{
				operacionesArchivo();
			}
			//else if(tokenizador->getTokenActual() == Lexico::sinTok || tokenizador->getTokenActual() == Lexico::cosTok || tokenizador->getTokenActual() == Lexico::tanTok ||
			//	tokenizador->getTokenActual() == Lexico::asinTok || tokenizador->getTokenActual() == Lexico::acosTok || tokenizador->getTokenActual() == Lexico::atanTok)
			//{
			//	operacionesTrigonometricas();
			//}
		}
	}
}	

void Parser::read()
{
	tokenizador->obtenerToken(); 
	if (tokenizador->getTokenActual()==Lexico::parentesisAbiertoTok)
	{
	   tokenizador->obtenerToken();
		if (tokenizador->getTokenActual()==Lexico::identificador)
		{
			int i = tablaDeSimbolos.buscar(tokenizador->getLexemaActual());
			if (i==0)
				notificadorError.mostrarError(tokenizador->getLineaActual(),11); //error 11: Identificador no declarado 
			else if(tablaDeSimbolos.getTipoDadoIndice(i) != Simbolo::VariableEntera
				&& tablaDeSimbolos.getTipoDadoIndice(i) != Simbolo::VariableReal)
			{
				notificadorError.mostrarError(tokenizador->getLineaActual(),39);//Se esperaba variable entera o real
			}
			else
			{
			   tokenizador->obtenerToken();
			   if (tokenizador->getTokenActual()!=Lexico::parentesisCerradoTok)
			   {
				notificadorError.mostrarError(tokenizador->getLineaActual(),40);//se esperaba parentesis cerrado
			   }
			   else
				   tokenizador->obtenerToken();
			}
		}
		else
			notificadorError.mostrarError(tokenizador->getLineaActual(),42);//se esperaba identificador

	}
	else
		notificadorError.mostrarError(tokenizador->getLineaActual(),38);//se esperaba parentesis abierto
}

void Parser::write()
{
	tokenizador->obtenerToken();
	if (tokenizador->getTokenActual()==Lexico::parentesisAbiertoTok)
	{
	   tokenizador->obtenerToken();
	   if (tokenizador->getTokenActual()==Lexico::cadenaTok)
	   {
		   tokenizador->obtenerToken();
		   if (tokenizador->getTokenActual() == Lexico::comaTok)
		   {
			   tokenizador->obtenerToken();
		   }
		   else
			   notificadorError.mostrarError(tokenizador->getLineaActual(),5); //falta coma o punto y coma
	   }

		if (tokenizador->getTokenActual()==Lexico::identificador)
		{
			int i = tablaDeSimbolos.buscar(tokenizador->getLexemaActual());
			if (i==0)
				notificadorError.mostrarError(tokenizador->getLineaActual(),11); //error 11: Identificador no declarado 
			else if(tablaDeSimbolos.getTipoDadoIndice(i) != Simbolo::VariableEntera
				&& tablaDeSimbolos.getTipoDadoIndice(i) != Simbolo::VariableReal
				&& tablaDeSimbolos.getTipoDadoIndice(i) != Simbolo::ConstanteEntera
				&& tablaDeSimbolos.getTipoDadoIndice(i) != Simbolo::ConstanteReal)
			{
				notificadorError.mostrarError(tokenizador->getLineaActual(),39);//Se esperaba variable entera o real
			}
			else
			{
			   tokenizador->obtenerToken();
			   if (tokenizador->getTokenActual()!=Lexico::parentesisCerradoTok)
			   {
				notificadorError.mostrarError(tokenizador->getLineaActual(),40);//se esperaba parentesis cerrado
			   }
			   else
				   tokenizador->obtenerToken();
			}
		}
		else
			notificadorError.mostrarError(tokenizador->getLineaActual(),42);//se esperaba identificador
	}
	else
		notificadorError.mostrarError(tokenizador->getLineaActual(),38);//se esperaba parentesis abierto
}
void Parser::www()
{
	tokenizador->obtenerToken(); 
	if (tokenizador->getTokenActual()==Lexico::parentesisAbiertoTok)
	{
	   tokenizador->obtenerToken();
	   if (tokenizador->getTokenActual()==Lexico::cadenaTok)
		{
			   tokenizador->obtenerToken();
			   if (tokenizador->getTokenActual()!=Lexico::parentesisCerradoTok)
			   {
					notificadorError.mostrarError(tokenizador->getLineaActual(),40);//se esperaba parentesis cerrado
			   }
			   else
					tokenizador->obtenerToken();
		}
	   else
			notificadorError.mostrarError(tokenizador->getLineaActual(),41);//se esperaba cadena
	}
	else
		notificadorError.mostrarError(tokenizador->getLineaActual(),38);//se esperaba parentesis abierto
}

void Parser::assign()
{
	tokenizador->obtenerToken(); 
	if (tokenizador->getTokenActual()==Lexico::parentesisAbiertoTok)
	{
	   tokenizador->obtenerToken();
	   if (tokenizador->getTokenActual()==Lexico::identificador)
		{
			int i = tablaDeSimbolos.buscar(tokenizador->getLexemaActual());
			if (i==0)
				notificadorError.mostrarError(tokenizador->getLineaActual(),11); //error 11: Identificador no declarado 
			else if(tablaDeSimbolos.getTipoDadoIndice(i) != Simbolo::VariableArchivo)
				notificadorError.mostrarError(tokenizador->getLineaActual(),43);//Se esperaba archivo
			else
			{
			   tokenizador->obtenerToken();
			   if (tokenizador->getTokenActual()!=Lexico::comaTok)
					notificadorError.mostrarError(tokenizador->getLineaActual(),5);//se esperaba coma
			   else
			   {
					tokenizador->obtenerToken();
					if (tokenizador->getTokenActual()!=Lexico::cadenaTok)
						notificadorError.mostrarError(tokenizador->getLineaActual(),41);//se esperaba cadena
					else
					{
					   tokenizador->obtenerToken();
					   if (tokenizador->getTokenActual()!=Lexico::parentesisCerradoTok)
							notificadorError.mostrarError(tokenizador->getLineaActual(),40);//se esperaba parentesis cerrado
					   else
							tokenizador->obtenerToken();
					}
			   }
			}
		}
		else
				notificadorError.mostrarError(tokenizador->getLineaActual(),42);//Se identificador
	}
	else
		notificadorError.mostrarError(tokenizador->getLineaActual(),38);//se esperaba parentesis abierto
}


void Parser::operacionesTrigonometricas()
{
	tokenizador->obtenerToken(); 
	if (tokenizador->getTokenActual()==Lexico::parentesisAbiertoTok)
	{
	   tokenizador->obtenerToken();
	   expresion();

	   if (tokenizador->getTokenActual()!=Lexico::parentesisCerradoTok)
	   {
			notificadorError.mostrarError(tokenizador->getLineaActual(),40);//se esperaba parentesis cerrado
	   }
	   else
			tokenizador->obtenerToken();
	}
	else
		notificadorError.mostrarError(tokenizador->getLineaActual(),38);//se esperaba parentesis abierto
}
void Parser::operacionesArchivo()
{
	tokenizador->obtenerToken(); 
	if (tokenizador->getTokenActual()==Lexico::parentesisAbiertoTok)
	{
	   tokenizador->obtenerToken();
	   if (tokenizador->getTokenActual()==Lexico::identificador)
		{
			int i = tablaDeSimbolos.buscar(tokenizador->getLexemaActual());
			if (i==0)
				notificadorError.mostrarError(tokenizador->getLineaActual(),11); //error 11: Identificador no declarado 
			else if(tablaDeSimbolos.getTipoDadoIndice(i) != Simbolo::VariableArchivo)
			{
				notificadorError.mostrarError(tokenizador->getLineaActual(),43);//Se esperaba archivo
			}
			else
			   tokenizador->obtenerToken();
			   if (tokenizador->getTokenActual()!=Lexico::parentesisCerradoTok)
			   {
					notificadorError.mostrarError(tokenizador->getLineaActual(),40);//se esperaba parentesis cerrado
			   }
			   else
					tokenizador->obtenerToken();
		}
	   else
			notificadorError.mostrarError(tokenizador->getLineaActual(),42);//se esperaba cadena
	}
	else
		notificadorError.mostrarError(tokenizador->getLineaActual(),38);//se esperaba parentesis abierto
}



void Parser::expresion()
{
 if (tokenizador->getTokenActual()==Lexico::masTok || tokenizador->getTokenActual()==Lexico::menosTok) 
 {
    tokenizador->obtenerToken();
    termino();
 }
 else 
    termino();

 while (tokenizador->getTokenActual()==Lexico::masTok || tokenizador->getTokenActual()==Lexico::menosTok) 
 {
       tokenizador->obtenerToken();
	   termino();
 }
}

void Parser::termino()
{
	factor();
	while (tokenizador->getTokenActual()==Lexico::porTok || tokenizador->getTokenActual()==Lexico::entreTok) 
	{
       tokenizador->obtenerToken();
       factor();
	}
}

void Parser::factor()
{
	int i;
	if (tokenizador->getTokenActual()==Lexico::identificador) 
	{
		i = tablaDeSimbolos.buscar(tokenizador->getLexemaActual());
		if (i==0) 
			notificadorError.mostrarError(tokenizador->getLineaActual(),11); //error 11: Identificador no declarado
		else
			if (tablaDeSimbolos.getTipoDadoIndice(i) == Simbolo::Procedimiento)
				notificadorError.mostrarError(tokenizador->getLineaActual(),21); //error 21: Una expresión no debe contener un identificador de procedimiento

		tokenizador->obtenerToken();
	}
	else if(tokenizador->getTokenActual() == Lexico::sinTok || tokenizador->getTokenActual() == Lexico::cosTok || tokenizador->getTokenActual() == Lexico::tanTok ||
		tokenizador->getTokenActual() == Lexico::asinTok || tokenizador->getTokenActual() == Lexico::acosTok || tokenizador->getTokenActual() == Lexico::atanTok)
	{
		operacionesTrigonometricas();
	}
	else
	{
		if (tokenizador->getTokenActual()==Lexico::numeroEntero || tokenizador->getTokenActual() == Lexico::numeroReal)
			tokenizador->obtenerToken();
		else
		{
			if (tokenizador->getTokenActual()==Lexico::parentesisAbiertoTok) 
			{
				tokenizador->obtenerToken();
				expresion();
				if (tokenizador->getTokenActual()==Lexico::parentesisCerradoTok)
					tokenizador->obtenerToken();
				else
					notificadorError.mostrarError(tokenizador->getLineaActual(),22); //error 22: Falta un paréntesis de cierre  
			}
			else 
			notificadorError.mostrarError(tokenizador->getLineaActual(),23); //error 23: El factor anterior no puede ir seguido de este símbolo 
		}
	}
}


void Parser::condicion()
{
	if (tokenizador->getTokenActual()==Lexico::oddTok) 
	{
		tokenizador->obtenerToken();
		expresion();
	}
	else 
	{
		expresion();
		if ((tokenizador->getTokenActual()!=Lexico::igualTok) && (tokenizador->getTokenActual()!=Lexico::diferenteTok) && (tokenizador->getTokenActual()!=Lexico::menorTok) && 
			(tokenizador->getTokenActual()!=Lexico::menorIgualTok) && (tokenizador->getTokenActual()!=Lexico::mayorTok) && (tokenizador->getTokenActual()!=Lexico::mayorIgualTok))
				notificadorError.mostrarError(tokenizador->getLineaActual(),20); //error 20: Se esperaba un operador relacional 
		else 
		{
			tokenizador->obtenerToken();
			expresion(); 
		}
	}
}
