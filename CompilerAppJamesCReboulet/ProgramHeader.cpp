#include "ProgramHeader.h"

ProgramHeader::ProgramHeader(Parser* parser)
{
	this->setParserPtr(parser);
	this->verifySyntaxCreateParseTree();
}

void ProgramHeader::verifySyntaxCreateParseTree()
{
	Token* currentToken = this->readNextToken();
	if (currentToken != nullptr)
	{
		//check to see that the first token equals "Program"
		if (currentToken->getTokenValue() == "program")
		{

		}

	}

}