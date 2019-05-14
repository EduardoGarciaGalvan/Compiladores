#include "stdafx.h"

#include "Compiler.h"

Compiler::Manager::Manager()
{
	err = gcnew ErrorsModule;
	lex = new LexAnalyzer(err);
}

Compiler::Manager::~Manager()
{
	if (lex != nullptr)
	{
		delete lex;
		lex = nullptr;
	}
}

cli::array<String^>^ Compiler::Manager::compileProgram(String ^ srcCode)
{
	cli::array<String^>^ CompilationDetails;
	lexAnalisys(srcCode);
	CompilationDetails = gcnew cli::array < String^>(1);
	CompilationDetails[0] = gcnew String("---Compile OK---");
	return CompilationDetails;
	// TODO: insert return statement here
}

void Compiler::Manager::lexAnalisys(String^srcCode)
{
	if (lex != nullptr)
	{
		lex->parseSourceCode((const char*) System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(srcCode).ToPointer());
	}
}