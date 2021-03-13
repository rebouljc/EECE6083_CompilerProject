#include "ProgramBody.h"
#include "Token.h"
#include "Declaration.h"
#include "TerminalNode.h"
#include "Statement.h"

ProgramBody::ProgramBody(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr)
{
	//Note: 3-13-2021: Added additional statement to set this node's parent node ptr, to enable reverse walking back up a tree.
	this->parentNodePtr = parentNodePtr;
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
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
	}

	else if (currentToken->getTokenValue() == "begin")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
		//We need to return here as well, so we can stop parsing declarations and begin parsing statements.
		return;
		
		
	}

	else
	{
		
		this->linkedMemberNonterminals.push_back(new Declaration(this->parserPtr, motherNode, this));
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
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
	}

	else if (currentToken->getTokenValue() == "end")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
	
	}

	else if (currentToken->getTokenValue() == "program")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
		return;
	}

	else
	{
		this->linkedMemberNonterminals.push_back(new Statement(this->parserPtr, motherNode, this));
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


	for (unsigned int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}
