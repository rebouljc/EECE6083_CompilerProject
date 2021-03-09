#include "AssignmentStatement.h"
#include "Destination.h"
#include "Identifier.h"
#include "Expression.h"

AssignmentStatement::AssignmentStatement(Parser* parser, ParseTreeNode* motherNode)
{
	this->setParserPtr(parser);
	this->verifySyntaxCreateParseTree(0, motherNode);
}

void AssignmentStatement::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{   //Needs to be modified for Statement
	Token* currentToken = this->parserPtr->getCurrentlyReadToken();


	this->linkedMemberNonterminals.push_back(new Destination(this->parserPtr, motherNode));
	ParseTreeNode* dest = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);

	if (!dest->getIsValid())
	{
		this->linkedMemberNonterminals.pop_back();
		return;  //We need to get out of here, since we know we do not have a valid <Destination>, since it doesn't begin with an identifier.
	}

	currentToken = this->parserPtr->readNextToken();
   
	
    //Read the next token, to prevent this from blowing up if we have a valid <Destination>
	

	if (currentToken->getTokenType() == "ASSIGNMENT")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
		
	}

	currentToken = this->parserPtr->readNextToken();
	
	this->linkedMemberNonterminals.push_back(new Expression(this->parserPtr, motherNode));
	ParseTreeNode* expr = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);
	if (!expr->getIsValid())
	{
		this->linkedMemberNonterminals.pop_back();
		return;  //Set is valid will be false here.
	}

	this->setIsValid(true);
	return;
	
	
}

ParseTreeNode* AssignmentStatement::getNodePtr()
{
	return this;

}

void AssignmentStatement::populateSearchResultsList(ParseTreeNode* motherNode)
{


	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}

void AssignmentStatement::populateLocalSearchResultsList()
{
	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList();
	}

}