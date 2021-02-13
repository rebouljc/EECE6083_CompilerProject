#include "Program.h"
#include "ProgramHeader.h"


Program::Program(Parser* parser)
{
	this->setParserPtr(parser);
	this->verifySyntaxCreateParseTree();
}

void Program::verifySyntaxCreateParseTree()
{
	//always make sure to pass the parser ptr.
	//create a program header.
	this->linkedMemberNonterminals.push_back(new ProgramHeader(this->parserPtr));


}
