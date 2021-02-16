#include "ProgramBody.h"
#include "Token.h"
#include "Declaration.h"
#include "TerminalNode.h"
#include "Statement.h"

ProgramBody::ProgramBody(Parser* parser, ParseTreeNode* motherNode)
{
	this->setParserPtr(parser);
	this->verifySyntaxCreateParseTree(0, motherNode);
}

void ProgramBody::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{   //Needs to be modified for program body. 
	
	//Both of these methods are recursive methods.  But, there can only be one "Program Body" so we have to divide the 
	//statements and the declarations up into separate methods.
	this->verifySyntaxCreateParseTreeDeclarationParser(motherNode);
	this->verifySyntaxCreateParseTreeStatementParser(motherNode);
	
}

void ProgramBody::verifySyntaxCreateParseTreeDeclarationParser(ParseTreeNode* motherNode)
{
	Token* currentToken = this->parserPtr->readNextToken();
	
	if (currentToken->getTokenValue() == ";")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
	}

	else if (currentToken->getTokenValue() == "begin")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
		return;
		
	}
	else
	{
		//Backup the read index, so the word "procedure" is not ignored.
		this->parserPtr->backupIndexToRead();
		this->linkedMemberNonterminals.push_back(new Declaration(this->parserPtr, motherNode));
		Declaration* decl = dynamic_cast<Declaration*>(this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1));
		if (!decl->getIsValid())
		{
			this->linkedMemberNonterminals.pop_back();
			
			//We have to backup the readIndex, so that the current token can be read by a future method.  Otherwise, "global" is ignored.
			
		}
		
	}
	this->verifySyntaxCreateParseTreeDeclarationParser(motherNode);
}
void ProgramBody::verifySyntaxCreateParseTreeStatementParser(ParseTreeNode* motherNode)
{
	Token* currentToken = this->parserPtr->readNextToken();

	if (currentToken->getTokenValue() == ";")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
	}

	else if (currentToken->getTokenValue() == "end")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
	
	}

	else if (currentToken->getTokenValue() == "program")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
		return;
	}

	else
	{
		this->linkedMemberNonterminals.push_back(new Statement(this->parserPtr, motherNode));
		Statement* stmt = dynamic_cast<Statement*>(this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1));
		if (!stmt->getIsValid())
		{
			this->linkedMemberNonterminals.pop_back();
			
		}
	}
	this->verifySyntaxCreateParseTreeStatementParser(motherNode);
}

ParseTreeNode* ProgramBody::getNodePtr()
{
	return this;

}

void ProgramBody::populateSearchResultsList(ParseTreeNode* motherNode)
{


	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}