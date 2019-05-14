#pragma once
#include "windows.h"
#include "Compiler.h"
#include "ErrorsModule.h"
#include "vcclr.h"
namespace Compiler {
	public class LexAnalyzer
	{
	public:
		LexAnalyzer(ErrorsModule ^ errorMod);
		~LexAnalyzer();
		bool parseSourceCode(const char *src);
	};
}

/*Abstraccion de datos
tipos de datos: int, float, string, bool, void
declaracion de variables: var id1, id2, id3[dim],...,idn:tipo
comentarios: /*...* /
Abstraccion de unidades
function idf(par1, par2:tipo ; par3:tipo):tipo
{
	var id1...:tipo;
	return expr;
}

if(Cond)
{}
else
{}

while(Cond)
{}
Switch(id)
{
	case intconst1:{}
	default:{}
}

for(id=expr;Cond;inc_dec)
{}

main
{}

print(exp_list);
read(exp);

Operadores
aritmeticos:+,-,*,/,%,^
logicos: &&, ||
logico_unario: !
relaciones: <,<=,>, >=, ==, !=
asignacion: =
palabras reservadas: var, int, float, string, bool, void, function,main,for,while,if,else,swicth,default,print,read,return

Errores:
Simbolo ilegal
Comentario sin cerrar
constante literal sin cerrar
Error en numero float

Ejemplos de tokens:
lexema|	tipo
33.5	FLOAT
48		INT
if		KEYWORD
!		op.logicounario
hola	ID

Definicion del lenguaje en BNF
<PROGRAMA>:=[<FUNCIONES>] <MAIN>
<FUNCIONES>:=<FUNCION>|<FUNCION><FUNCIONES>
<FUNCION>:='function'<ID><PARAM>':'<TIPO><BLOCK_STATEMENTS>

Tarea: Terminar ID con sus respectivos elementos
<ID>:=*/