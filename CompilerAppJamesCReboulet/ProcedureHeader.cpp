#include "ProcedureHeader.h"
#include "Identifier.h"
#include "TypeMark.h"

ProcedureHeader::ProcedureHeader(Parser* parser, ParseTreeNode* motherNode)
{
	this->setParserPtr(parser);
	this->verifySyntaxCreateParseTree(0, motherNode);
}

void ProcedureHeader::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{   //Needs to be modified for program body.  Make it recursive to handle multiple declarations and statements.
	//Read the next token here.
	Token* currentToken = parserPtr->readNextToken();
	if (tokenCounter == 0)
	{
		if (currentToken->getTokenValue() == "procedure")
		{
			this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
		}

		else
		{
			//get out of here and backup the token index.
			parserPtr->backupIndexToRead();
			return;
		}
	}
	else if (tokenCounter == 1)
	{
		if (currentToken->getTokenType() == "IDENTIFIER")
		{
			this->linkedMemberNonterminals.push_back(new Identifier(currentToken, motherNode, "GLOBAL"));
		}

		else
		{
			//Throw an exception.  Return for now.
			parserPtr->backupIndexToRead();
			return;
		}
	}
	else if (tokenCounter == 2)
	{
		if (currentToken->getTokenValue() == ":")
		{
			this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
		}

		else
		{
			//Throw an exception.  Return for now.
			parserPtr->backupIndexToRead();
			return;
		}
	}

	else if (tokenCounter == 3) //If it is equal to 3 and we have made it this far, we need a type mark.
	{
		this->linkedMemberNonterminals.push_back(new TypeMark(this->parserPtr, motherNode));
	}
	else
	{
		//Throw an exception and/or generate an error.
		this->parserPtr->backupIndexToRead();
		return;
		
	}
	++tokenCounter;
	this->verifySyntaxCreateParseTree(tokenCounter, motherNode);
	return;

}

ParseTreeNode* ProcedureHeader::getNodePtr()
{
	return this;

}

void ProcedureHeader::populateSearchResultsList(ParseTreeNode* motherNode)
{


	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}