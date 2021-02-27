#include "IfStatement.h"
#include "Expression.h"
#include "Identifier.h"
#include "Statement.h"
#include "TerminalNode.h"


IfStatement::IfStatement(Parser* parser, ParseTreeNode* motherNode)
{
	this->setParserPtr(parser);
	this->verifySyntaxCreateParseTree(0, motherNode);
}
void IfStatement::dealWithThenOrElse(ParseTreeNode* motherNode, int tokenCounter)
{
	Token* currentToken = this->parserPtr->getCurrentlyReadToken();

	if (currentToken->getTokenValue() == "then" || currentToken->getTokenValue() == "else")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
	}

	else
	{
		this->linkedMemberNonterminals.push_back(new Statement(this->parserPtr, motherNode));
		bool isValid = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);
		if (!isValid)
		{
			this->linkedMemberNonterminals.pop_back();
			return; //Here, we return at the first point that there is no valid statement, or we will infinitely recurse here.
		}

		currentToken = this->parserPtr->readNextToken();
		if (currentToken->getTokenValue() == ";")
		{
			this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
		}
	}
	++tokenCounter;
	currentToken = this->parserPtr->readNextToken();
	this->dealWithThenOrElse(motherNode, tokenCounter);
	return;
}

void IfStatement::dealWithIf(ParseTreeNode* motherNode, int tokenCounter)
{
	Token* currentToken = this->parserPtr->getCurrentlyReadToken();

	if (currentToken->getTokenValue() == "if")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
	}

	else if (currentToken->getTokenValue() == "(")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
	}
	else if (currentToken->getTokenValue() == ")")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
		return;
	}

	else
	{
		this->linkedMemberNonterminals.push_back(new Expression(this->parserPtr, motherNode));
		bool isValid = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);
		if (!isValid)
		{
			//We throw an error here, since an expression is required.
			//Right now, we will return, though to prevent infinite recursion.
			return;
		}
	}
	++tokenCounter;
	currentToken = this->parserPtr->readNextToken();
	this->dealWithIf(motherNode, tokenCounter);
	return;
}

void IfStatement::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{   //Needs to be modified for program body.  Make it recursive to handle multiple declarations and statements.
	Token* currentToken = parserPtr->getCurrentlyReadToken();

	if (currentToken->getTokenValue() == "if")
	{
		this->dealWithIf(motherNode, 0);
	}

	if (currentToken->getTokenValue() == "then")
	{
		this->dealWithThenOrElse(motherNode, 0);
	}

	else if (currentToken->getTokenValue() == "else")
	{
		this->dealWithThenOrElse(motherNode, 0);
	}

	else if (currentToken->getTokenValue() == "end") //Note:  We can't recurse here, since we are expecting the sequence of tokens "end" + "if"
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
		currentToken = this->parserPtr->readNextToken();

		if (currentToken->getTokenValue() == "if")
		{
			this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
			return;
		}

	}
	//Need to remember to recurse.
	++tokenCounter;
	this->parserPtr->readNextToken();
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