#include "Lexer.h"
#include "Parser.h"
#include "CodeGen.h"

int main()
{
	std::string input;
	std::ifstream f("input.c", std::ios::in);
	while (!f.eof())
	{
		std::string tin;
		std::getline(f, tin);
		input += tin;
	}


	Lexer* lexer = new Lexer(input);
	Parser* parser = new Parser(lexer->LexicalAnalyisis());
	parser->parse();
	parser->printTree(nullptr);

	CodeGen* codeGen = new CodeGen();
	codeGen->GenCode(parser->getAST());
	codeGen->printGeneratedCode();

	delete lexer;
	delete parser;
	delete codeGen;

	return 0;
}