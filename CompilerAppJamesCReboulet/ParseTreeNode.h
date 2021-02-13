#pragma once
#include <vector>
#include "Token.h"
#include "Parser.h"

class ParseTreeNode
{
public:
	
protected:
	//methods
	void setParserPtr(Parser* parserPtr);
	virtual void verifySyntaxCreateParseTree() { return; };
	Token* readNextToken();

	//member variables
	int indexToRead = 0;
	Parser* parserPtr;
};