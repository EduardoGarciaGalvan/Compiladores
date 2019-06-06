#pragma once
#include "windows.h"
#include "ErrorsModule.h"
#include "Token.h"
#include "vcclr.h"
#include "vector"
#include "string"
#include "map"

#define LEX_INVALID_CHARACTER "Invalid character"
#define STRING_NOT_CLOSED "stirng not closed"
#define COMMENT_NOT_CLOSED "comment not closed"
#define INVALID_FLOAT "invalid float"
#define INVALID_OP_LOG "invalid op log"
namespace Compiler {
	public class LexAnalyzer
	{
	public:
		LexAnalyzer(ErrorsModule ^ errorMod);
		~LexAnalyzer();
		void clearTokens();
		bool parseSourceCode(const char *src);
		void getTokens(std::vector<Token*>*tokensVec);
		void addToken(const char * lex, int lineNum, TOKEN_TYPE tp);
		Token* getNextToken();
		Token* getPrevToken();
		Token* getPeekToken();
	private:
		int m_numLine;
		msclr::gcroot<ErrorsModule^> m_refErrorsMod;
		std::map<std::string, std::string> m_keywords;
		std::vector<std::string> m_Keyword = { "var", "int","float","main",
			"string","bool","void","function","for","while","if","else","switch",
			"case","default","print","read","return","true","false","inc","dec"};
		std::vector<std::string> m_separator = { ";",":", "," };
		std::vector<std::string> m_op_arit = { "+","-","*","/","%","^" };
		std::vector<std::string> m_op_dim = { "(",")","[","]" };
		std::vector<std::string> m_op_agr = { "{","}" };
		std::vector<std::string> m_op_log = { "||","&&" };
		std::vector<std::string> m_op_log_unario = { "!"};
		std::vector<std::string> m_op_rel = { "<","<=",">", ">=", "==", "!="};
		std::vector<std::string> m_assigmment = { "=" };
		std::vector<std::string> m_symbol = { "#","$","@","ñ","Ñ","~", "¼" };
		std::vector<Token*> m_Tokens;

		void wordParse(const char* src, int& count);
		void intParse(const char* src, int& count);
		void floatParse(const char* src, int& count, std::string str = "");
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
palabras reservadas: var, int, float, string, bool, void, function,main,for,while,if,else,swicth,default,print,read,return,case,true,false,inc,dec

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
<PROGRAMA>::=[<VARIABLES>][<FUNCIONES>]<MAIN>
<FUNCIONES>::=<FUNCION>[<FUNCIONES>]
<FUNCION>::='function'<ID><PARAM>':'<TIPO_FUNCION><BLOCK_FUNCTION>

<GRUPO_VARIABLES>::=<VARIABLES>|<VARIABLES>[<GRUPO_VARIABLES>]
<VARIABLES>::='var'<GRUPO_ID>':'<TIPO>';'
<GRUPO_ID>::=<ID>[<DIMENSION>]|<ID>[<DIMENSION>][','<GRUPO_ID>]
<TIPO>::='int'|'bool'|'float'|'string'
<TIPO_FUNCION>::=<TIPO>|'VOID'
<DIMENSION>::='['<NUM_POS>']'
<PARAM>::= '('<GRUPO_PARAM>')'
<GRUPO_PARAM>::=<GRUPO_ID>':'<TIPO>[';'<GRUPO_PARAM>]
<STATEMENTS>::=<STATEMENT>[<STATEMENT>]
<STATEMENT>::=<IF>|<WHILE>|<FOR>|<SWICTH>|<RETURN>|<FUNC_CALL>|<READ>|<PRINT>|<ASIGNACION>
	<IF>::='if''('<EXP_LOG>')'<BLOCK_ST>
	<WHILE>::='while''('<EXP_LOG>')'<BLOCK_ST>
	<READ>::='read''('<EXP_LOG>')'';'
	<PRINT>::='print''('<EXP_LOG>')'';'
<OP_ARIT>::='<'|'<='|'>'|'>='|'=='|'!='
<OP_REL>::='&&'|'||'
<OP_LOG_UNARIO>::='!'
<CONST_LOG>::='true'|'false'
<CONSTANT>::=<CONST_LOG>|<CONST_INT>|<CONST_FLOAT>|<CONST_LITERAL>
<BLOCK_STATEMENT>::='{'[<STATEMENTS>]'}'
<BLOCK_FUNCION>::='{'[<VARIABLES>][<STATEMENTS>]'}'
<ASIGNACION>::=<ID>'='<EXP_LOG>';'
<RETURN>::='return'<EXP_LOG>';'
<FUNC_CALL>::=<ID>'('<EXP_LOG_LIST>')'';'
<INC_DEC>::='inc'<NUM_POS>|'dec'<NUM_POS>
<FOR>::='for''('<ASIGNACION><EXP_LOG>';'<INC_DEC>')'<BLOCK_ST>
<SWICTH>::='swicth''('<ID>[<DIMENSION>]')''{'<CASES><DEFAULT>'}'
	<CASES>::='case'<NUM_POS>':'<BLOCK_ST>[<CASES>]
	<DEFAULT>::='default'':'<BLOCK_ST>
Analizador léxico
-Estado inicial
-
-
-
-

TIPO_FUNCION	1
TIPO			1
LETRA			1
ID				1
VARIABLES		1
FUNCION			1
PROGRAMA		1
MAIN			1
NUMERO			1
DIMENSION		1
PARAM			1
IF				1
WHILE			1
SWICTH			1
FOR				1
STATEMENTS		1
STATEMENT		1
ASIGNACION		1
RETURN			1
INC_DEC			1
CONSTANT		1
CONST_LOG_UNARIO1
FUNC_CALL		1
BLOCK_ST		1
OP_LOG_UNARIO	1
FUNC_ST			0
READ			1
PRINT			1
OP_LOG			1
OP_ARIT			1
OP_REL			1
EXP_LOG			0

<EXP_LOG>::=[<UNARY_OP_LOG>]<TERM><OPERATOR><EXP_LOG>||[<UNARY_OP_LOG>]<TERM>
<TERM>::='('<EXP_LOG>')'|<CONSTANT>|<FUNC_CALL>|<ID>[<DIMENSION>]

TAREA:
Realizar la EXP_LOG(expresion logica)

Tarea: Terminar ID con sus respectivos elementos
<ID>::=<LETRA>[<ID_VALID_CHAR>]|'_'<ID_VALID_CHAR>
<ID_VALID_CHAR>::=<LETRA>[<ID_VALID_CHAR>]|<DIGITO>[<ID_VALID_CHAR>]|'_'<ID_VALID_CHAR>
<LETRAS>::=<LETRA>|<LETRAS>
<LETRA>::=|'A'|'a'|'B'|'b'|'C'|'c'|...|'Y'|'y'|'Z'|'z'|
<NUMERO>::=<DIGITO>|<NUMERO>
<DIGITO>::=|'1'|'2'|'3'|'4'|'5'|'6'|'7'|'8'|'9'|'0'

Tabla de simbolos
Contiene ID´s y nombres de funcion
ejemplo:
var x,w[5]:float;
function z():void
{
	var x,s:int;
}
function volcylinder(x, radio:float):float
{
	var s:float;
}
"x"|categoria(global,local)|Tipo(float,int,etc)|Dimension|valor|ptr. NodoLocal|

2 parcial
Estrategias de recuperacion de errores
var x : int; bien
var : int; mal
var a int; mal
var x :; mal

*/