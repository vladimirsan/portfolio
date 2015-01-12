#include "Lexico.h"

#include <utility>
#include <iostream>

// Palabras Clave
//“begin”+“call”+“const”+“do”+“end”+“if”+“odd”+“procedure”+“then”+“var”+ “while”


using namespace lexicoGrafico;
using namespace std;

Lexico::Lexico(bool ingles)
{
	if(ingles)
		llenarMapaPalabrasReservadas();
	else
		llenarMapaPalabrasReservadasEspanhol();

	llenarMapaSimbolosEspeciales();
	llenarListaSimbolosEspecialesTamanho1();
	llenarMapaSimbolosEspecialesComplejos();

	//programar aca lo de ingles/espanhol
}

void Lexico::llenarMapaPalabrasReservadasEspanhol()
{
	mapaPalabrasReservadas.insert(pair<string,Token>("comienza",beginTok));
	mapaPalabrasReservadas.insert(pair<string,Token>("llamar",callTok));
	mapaPalabrasReservadas.insert(pair<string,Token>("const",constTok));
	mapaPalabrasReservadas.insert(pair<string,Token>("hacer",doTok));
	mapaPalabrasReservadas.insert(pair<string,Token>("termina",endTok));
	mapaPalabrasReservadas.insert(pair<string,Token>("si",ifTok));
	mapaPalabrasReservadas.insert(pair<string,Token>("impar",oddTok));
	mapaPalabrasReservadas.insert(pair<string,Token>("procedimiento",procedureTok));
	mapaPalabrasReservadas.insert(pair<string,Token>("entonces",thenTok));
	mapaPalabrasReservadas.insert(pair<string,Token>("var",varTok));
	mapaPalabrasReservadas.insert(pair<string,Token>("mientras",whileTok));	

	mapaPalabrasReservadas.insert(pair<string,Token>("entero",tipoIntTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("real",tipoRealTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("archivo",tipoFileTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("caso",caseTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("de",ofTok));	

	mapaPalabrasReservadas.insert(pair<string,Token>("leer",readTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("leerln",readLnTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("escribir",writeTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("escribirln",writeLnTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("www",wwwTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("seno",sinTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("coseno",cosTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("tangente",tanTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("atangente",atanTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("acoseno",acosTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("aseno",asinTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("asignar",assignTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("limpiar",resetTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("cerrar",closeTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("mostrar",displayTok));	
}

void Lexico::llenarMapaPalabrasReservadas()
{
	//Llenamos el arreglo de cadenas a token
	//mapaPalabrasReservadas.insert(pair<string,Token>("nulo",nulo));
	mapaPalabrasReservadas.insert(pair<string,Token>("begin",beginTok));
	mapaPalabrasReservadas.insert(pair<string,Token>("call",callTok));
	mapaPalabrasReservadas.insert(pair<string,Token>("const",constTok));
	mapaPalabrasReservadas.insert(pair<string,Token>("do",doTok));
	mapaPalabrasReservadas.insert(pair<string,Token>("end",endTok));
	mapaPalabrasReservadas.insert(pair<string,Token>("if",ifTok));
	mapaPalabrasReservadas.insert(pair<string,Token>("odd",oddTok));
	mapaPalabrasReservadas.insert(pair<string,Token>("procedure",procedureTok));
	mapaPalabrasReservadas.insert(pair<string,Token>("then",thenTok));
	mapaPalabrasReservadas.insert(pair<string,Token>("var",varTok));
	mapaPalabrasReservadas.insert(pair<string,Token>("while",whileTok));	

	mapaPalabrasReservadas.insert(pair<string,Token>("integer",tipoIntTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("real",tipoRealTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("file",tipoFileTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("case",caseTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("of",ofTok));	

	mapaPalabrasReservadas.insert(pair<string,Token>("read",readTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("readln",readLnTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("write",writeTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("writeln",writeLnTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("www",wwwTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("sin",sinTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("cos",cosTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("tan",tanTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("atan",atanTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("acos",acosTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("asin",asinTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("assign",assignTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("reset",resetTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("close",closeTok));	
	mapaPalabrasReservadas.insert(pair<string,Token>("display",displayTok));	
}

void Lexico::llenarMapaSimbolosEspeciales()
{
	// de longitud 1 menorTok,mayorTok,masTok,menosTok,porTok,entreTok,
			//parentesisAbiertoTok,parentesisCerradoTok,igualTok,
			//puntoTok,comaTok,puntoYcomaTok,
	
	mapaSimbolosEspeciales.insert(pair<string,Token>("<",menorTok));
	mapaSimbolosEspeciales.insert(pair<string,Token>(">",mayorTok));
	mapaSimbolosEspeciales.insert(pair<string,Token>("+",masTok));
	mapaSimbolosEspeciales.insert(pair<string,Token>("-",menosTok));
	mapaSimbolosEspeciales.insert(pair<string,Token>("*",porTok));
	mapaSimbolosEspeciales.insert(pair<string,Token>("/",entreTok));
	mapaSimbolosEspeciales.insert(pair<string,Token>("(",parentesisAbiertoTok));
	mapaSimbolosEspeciales.insert(pair<string,Token>(")",parentesisCerradoTok));
	mapaSimbolosEspeciales.insert(pair<string,Token>("=",igualTok));
	mapaSimbolosEspeciales.insert(pair<string,Token>(".",puntoTok));
	mapaSimbolosEspeciales.insert(pair<string,Token>(",",comaTok));
	mapaSimbolosEspeciales.insert(pair<string,Token>(";",puntoYcomaTok));
	mapaSimbolosEspeciales.insert(pair<string,Token>("\"",comillasTok));

	mapaSimbolosEspeciales.insert(pair<string,Token>(":",dosPuntosTok)); 

	mapaSimbolosEspeciales.insert(pair<string,Token>("{",llaveInicioTok));
  		
	// de longitud 2 menorIgualTok,diferenteTok,mayorIgualTok,asignacionTok
	mapaSimbolosEspeciales.insert(pair<string,Token>("<=",menorIgualTok));
	mapaSimbolosEspeciales.insert(pair<string,Token>("<>",diferenteTok));
	mapaSimbolosEspeciales.insert(pair<string,Token>(">=",mayorIgualTok));
	mapaSimbolosEspeciales.insert(pair<string,Token>(":=",asignacionTok));
	

	// de longitud 3
	/*mapaSimbolosEspeciales.insert(pair<string,Token>("<=.",menorIgualPuntoTok));
	mapaSimbolosEspeciales.insert(pair<string,Token>("<>.",menorMayorPuntoTok));
	mapaSimbolosEspeciales.insert(pair<string,Token>(">=.",mayorIgualPuntoTok));*/
	
	//A partir de aca son los simbolos inversos 

	//palabras clave
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(nulo,"nulo"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(identificador,"identificador"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(numeroEntero,"numeroEntero"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(numeroReal,"numeroReal"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(beginTok,"beginTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(callTok,"callTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(constTok,"constTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(doTok,"doTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(endTok,"endTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(ifTok,"ifTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(oddTok,"oddTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(procedureTok,"procedureTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(thenTok,"thenTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(varTok,"varTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(whileTok,"whileTok"));

	mapaPalabrasReservadasInverso.insert(pair<Token,string>(tipoIntTok,"tipoIntTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(tipoRealTok,"tipoRealTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(tipoFileTok,"tipoFileTok"));

	mapaPalabrasReservadasInverso.insert(pair<Token,string>(caseTok,"caseTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(ofTok,"ofTok"));

	mapaPalabrasReservadasInverso.insert(pair<Token,string>(readTok,"readTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(readLnTok,"readLnTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(writeTok,"writeTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(writeLnTok,"writeLnTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(wwwTok,"wwwTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(sinTok,"sinTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(cosTok,"cosTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(tanTok,"tanTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(asinTok,"asinTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(acosTok,"acosTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(atanTok,"atanTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(assignTok,"assignTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(resetTok,"resetTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(closeTok,"closeTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(displayTok,"displayTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(cadenaTok,"cadenaTok"));

	
	
	// especiales

	//longitud 1
	
	// de longitud 1 menorTok,mayorTok,masTok,menosTok,porTok,entreTok,parentesisAbiertoTok,parentesisCerradoTok,igualTok,puntoTok,comaTok,puntoYcomaTok
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(menorTok,"menorTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(mayorTok,"mayorTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(masTok,"masTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(menosTok,"menosTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(porTok,"porTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(entreTok,"entreTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(parentesisAbiertoTok,"parentesisAbiertoTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(parentesisCerradoTok,"parentesisCerradoTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(igualTok,"igualTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(puntoTok,"puntoTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(comaTok,"comaTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(puntoYcomaTok,"puntoYcomaTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(dosPuntosTok,"dosPuntosTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(comillasTok,"comilasTok"));

	// de longitud 2   menorIgualTok,diferenteTok,mayorIgualTok,asignacionTok
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(menorIgualTok,"menorIgualTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(diferenteTok,"diferenteTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(mayorIgualTok,"mayorIgualTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(asignacionTok,"asignacionTok"));

	// de longitud 3
	/*mapaPalabrasReservadasInverso.insert(pair<Token,string>(menorIgualPuntoTok,"menorIgualPuntoTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(menorMayorPuntoTok,"menorMayorPuntoTok"));
	mapaPalabrasReservadasInverso.insert(pair<Token,string>(mayorIgualPuntoTok,"mayorIgualPuntoTok"));*/
}

void Lexico::llenarListaSimbolosEspecialesTamanho1()
{
	simbolosEspecialesTamanho1.push_back('+');
	simbolosEspecialesTamanho1.push_back('-');
	simbolosEspecialesTamanho1.push_back('*');
	simbolosEspecialesTamanho1.push_back('/');
	simbolosEspecialesTamanho1.push_back('(');
	simbolosEspecialesTamanho1.push_back(')');
	simbolosEspecialesTamanho1.push_back('=');
	simbolosEspecialesTamanho1.push_back('.');
	simbolosEspecialesTamanho1.push_back(',');
	simbolosEspecialesTamanho1.push_back(';');
	simbolosEspecialesTamanho1.push_back('{');
	simbolosEspecialesTamanho1.push_back('\"');
}

void Lexico::llenarMapaSimbolosEspecialesComplejos()
{

	vector<std::string> vectorDospuntos;
	vectorDospuntos.push_back(":=");
	simbolosEspecialesComplejos.insert(pair<char,vector<string>>(':',vectorDospuntos));

	vector<std::string> vectorMenor;
	vectorMenor.push_back("<=");
	vectorMenor.push_back("<>");
	simbolosEspecialesComplejos.insert(pair<char,vector<string>>('<',vectorMenor));
	
	vector<std::string> vectorMayor;
	vectorMayor.push_back(">=");
	simbolosEspecialesComplejos.insert(pair<char,vector<string>>('>',vectorMayor));
}