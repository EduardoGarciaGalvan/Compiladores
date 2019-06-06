#pragma once
#include <string>
using namespace System;

namespace Compiler
{
	public enum TOKEN_TYPE
	{
		UNDEFINED = 0,
		ID,
		INT,
		FLOAT,
		KEYWORD,
		OPERATORARITHMETIC,
		OPERATORLOGIC,
		OPERATORLOGICUNARIO,
		ASIGNATION,
		SEPARATOR,
		RELATIONAL,
		STRING,
		INC,
		DEC
	};
	public class Token
	{
	public:
		Token(std::string lex, TOKEN_TYPE tp, int lineNum);
		~Token();
		std::string getLex() const;
		std::string getTypestr() const;
		int getType() const;
		int getLineNum() const;
	private:
		std::string m_Lex;
		int m_lineNumber;
		TOKEN_TYPE m_Type;
	};
}
