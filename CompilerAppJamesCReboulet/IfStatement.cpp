#include "IfStatement.h"
#include "Expression.h"
#include "Identifier.h"


IfStatement::IfStatement(Parser* parser, ParseTreeNode* motherNode)
{
	this->setParserPtr(parser);
	this->verifySyntaxCreateParseTree(0, motherNode);
}

void IfStatement::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{   //Needs to be modified for program body.  Make it recursive to handle multiple declarations and statements.
	Token* currentToken = parserPtr->getCurrentlyReadToken();

	if (currentToken->getTokenValue() == "if")
	{
		this->linkedMemberNonterminals.push_back(new Identifier(currentToken, motherNode, "GLOBAL"));
	}

	else if (tokenCounter == 1 && currentToken->getTokenValue() == "then")
	{
		this->linkedMemberNonterminals.push_back(new Expression(this->parserPtr, motherNode));
		//Check if it is valid.  If it is not, remove it.
		bool isValid = !this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1)->getIsValid();
		if (!isValid)
		{
			//Here, we throw an error, since every if statement is required to have an expression, so we had better have a valid expression.
		}
	}

	else if (tokenCounter == 2 && currentToken->getTokenValue() == "then")
	{
		//TODO: START HERE!
	}

	currentToken = this->parserPtr->readNextToken();
	++tokenCounter;
	this->verifySyntaxCreateParseTree(tokenCounter, motherNode);

}

ParseTreeNode* IfStatement::getNodePtr()
{
	return this;

}

void IfStatement::populateSearchResultsList(ParseTreeNode* motherNode)
{


	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}