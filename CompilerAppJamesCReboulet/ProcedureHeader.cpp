#include "ProcedureHeader.h"
#include "Identifier.h"

ProcedureHeader::ProcedureHeader(Parser* parser, ParseTreeNode* motherNode)
{
	this->setParserPtr(parser);
	this->verifySyntaxCreateParseTree(0, motherNode);
}

void ProcedureHeader::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{   //Needs to be modified for program body.  Make it recursive to handle multiple declarations and statements.
	//Read the next token here.
	Token* currentToken = parserPtr->readNextToken();
	if (currentToken->getTokenValue() == "procedure")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
	}

	else if (currentToken->getTokenType() == "IDENTIFIER")
	{
		this->linkedMemberNonterminals.push_back(new Identifier(currentToken, motherNode, "GLOBAL"));
	}

	else
	{
		this->parserPtr->backupIndexToRead();
		return;
		
	}

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