#include "stdafx.h"
#include "Token.h"

 std::string m_Typestr [] = {
	"UNDEFINED",
		"ID",
		"INT",
		"FLOAT",
		"KEYWORD",
		"OPERATORARITHMETIC",
		"OPERATORLOGIC",
		"OPERATORLOGICUNARIO",
		"ASIGNATION",
		"SEPARATOR",
		"RELATIONAL",
		"STRING",
		"INC",
		"DEC"
};

Compiler::Token::Token(std::string lex, TOKEN_TYPE tp, int lineNum)
{
	m_Lex = lex;
	m_lineNumber = lineNum;
	m_Type = tp;
}

Compiler::Token::~Token()
{
}

std::string Compiler::Token::getLex() const
{
	return m_Lex;
}

std::string Compiler::Token::getTypestr() const
{
	return m_Typestr[0];
}

int Compiler::Token::getType() const
{
	return m_Type;
}

int Compiler::Token::getLineNum() const
{
	return m_lineNumber;
}
