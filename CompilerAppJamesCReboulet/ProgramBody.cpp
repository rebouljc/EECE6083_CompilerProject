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
	printf("\nProgramBody_CurrentToken = %s", currentToken->getTokenValue().c_str());
	
	if (!this->linkedMemberNonterminals.empty() &&
		dynamic_cast<Declaration*>(this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1)) && 
		currentToken->getTokenValue() == ";")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
	}

	else if (currentToken->getTokenValue() == "begin")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
		//We need to return here as well, so we can stop parsing declarations and begin parsing statements.
		return;
		
		
	}

	else
	{
		
		this->linkedMemberNonterminals.push_back(new Declaration(this->parserPtr, motherNode));
		ParseTreeNode* decl= this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);
		if (!decl->getIsValid())
		{
			this->linkedMemberNonterminals.pop_back();
		
		}
		
	}
	this->verifySyntaxCreateParseTreeDeclarationParser(motherNode);
}
void ProgramBody::verifySyntaxCreateParseTreeStatementParser(ParseTreeNode* motherNode)
{
	Token* currentToken = this->parserPtr->readNextToken();

	if (!this->linkedMemberNonterminals.empty() &&
		dynamic_cast<Statement*>(this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1)) && 
		currentToken->getTokenValue() == ";")
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
		ParseTreeNode* testNode = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);
		if (!testNode->getIsValid())
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

void ProgramBody::populateLocalSearchResultsList()
{
	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList();
	}

}