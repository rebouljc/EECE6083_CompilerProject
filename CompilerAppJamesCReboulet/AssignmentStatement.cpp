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
	Token* currentToken = parserPtr->getCurrentlyReadToken();
	this->linkedMemberNonterminals.push_back(new Destination(this->parserPtr, motherNode));
	ParseTreeNode* dest = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);
	if (!dest->getIsValid())
	{
		this->linkedMemberNonterminals.pop_back();
		return;  //We need to get out of here, since we know we do not have a valid <Destination>, since it doesn't begin with an identifier.
	}

	else if (currentToken->getTokenType() == "ASSIGNMENT")
	{
		this->linkedMemberNonterminals.push_back(new Identifier(currentToken, motherNode, "GLOBAL"));
	}

	else
	{
		this->linkedMemberNonterminals.push_back(new Expression(this->parserPtr, motherNode));
		ParseTreeNode* expr = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);
		if (!expr->getIsValid())
		{
			this->linkedMemberNonterminals.pop_back();
		}
		this->setIsValid(true);
		return;
	}
	++tokenCounter;
	currentToken = parserPtr->readNextToken();
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