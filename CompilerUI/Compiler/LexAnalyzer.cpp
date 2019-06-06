#include "stdafx.h"
#include "LexAnalyzer.h"
#include <string>
using namespace std;


Compiler::LexAnalyzer::LexAnalyzer(ErrorsModule ^ errorMod)
{
	m_refErrorsMod = errorMod;
}

Compiler::LexAnalyzer::~LexAnalyzer()
{
}

void Compiler::LexAnalyzer::clearTokens()
{
}

bool Compiler::LexAnalyzer::parseSourceCode(const char * src)
{
	int count = 0;
	while (src[count] != '\0')
	{
		if (src[count] >= 'a' && src[count] <= 'z' || src[count] >= 'A' && src[count] <= 'Z')
		{
			wordParse(src, count);
		}
		if (src[count] >= 0 && src[count] <= 9)
		{
			intParse(src, count);
		}
		if (src[count] == '.')
		{
			floatParse(src, count);
		}

	}
	return false;
}

void Compiler::LexAnalyzer::getTokens(std::vector<Token*>* tokensVec)
{
}

void Compiler::LexAnalyzer::addToken(const char * lex, int lineNum, TOKEN_TYPE tp)
{
}

Compiler::Token * Compiler::LexAnalyzer::getNextToken()
{
	return nullptr;
}

Compiler::Token * Compiler::LexAnalyzer::getPrevToken()
{
	return nullptr;
}

Compiler::Token * Compiler::LexAnalyzer::getPeekToken()
{
	return nullptr;
}

void Compiler::LexAnalyzer::wordParse(const char * src, int & count)
{
	while (src[count] >= 'a' && src[count] <= 'z' || src[count] >= 'A' && src[count] <= 'Z' || src[count] >= 0 && src[count] <= 9)
	{

	}
}

void Compiler::LexAnalyzer::intParse(const char * src, int & count)
{
	while (src[count] >= 0 && src[count] <= 9)
	{

	}
	if (src[count] == '.')
	{
		floatParse(src, count);
	}
}

void Compiler::LexAnalyzer::floatParse(const char * src, int & count, std::string str)
{
	while (src[count] >= 0 && src[count] <= 9)
	{

	}
	if (src[count])
	{

	}
}
