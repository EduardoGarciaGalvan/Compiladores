#pragma once
#include "windows.h"

#include "ErrorsModule.h"
#include "LexAnalyzer.h"
using namespace System;

namespace Compiler {
	public ref class Manager
	{
	public:
		Manager();
		~Manager();
		cli::array<String^>^compileProgram(String^srcCode);
	private:
		void lexAnalisys(String^srcCode);
		LexAnalyzer *lex;
		ErrorsModule ^err;
		// TODO: Add your methods for this class here.
	};
}
