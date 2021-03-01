#include "Factor.h"
#include "TerminalNode.h"
#include "Expression.h"
#include "Number.h"
#include "StringLiteral.h"

//2-23-2021: Code needs to be modified.  This is type mark code.
Factor::Factor(Parser* parser, ParseTreeNode* motherNode)
{
	this->setParserPtr(parser);
	this->verifySyntaxCreateParseTree(0, motherNode);
}

void Factor::dealWithExpression(ParseTreeNode* motherNode, int tokenCounter)
{
	Token* currentToken = parserPtr->getCurrentlyReadToken();
	if (currentToken->getTokenValue() == ")") //Note:  We can't recurse here, since we are expecting the sequence of tokens "end" + "if"
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
		//We need to return out of here, so we can stop the recursion.
		return;
	}

	else
	{
		this->linkedMemberNonterminals.push_back(new Expression(this->parserPtr, motherNode));
	}
	++tokenCounter;
	currentToken = parserPtr->readNextToken();
	this->dealWithExpression(motherNode, tokenCounter);
}

void Factor::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{
	//Doing this with modified code from If_Statement.  This method is PARTIALLY RECURSIVE, though.  However, this->dealWithExpression(...) IS.
	
	Token* currentToken = parserPtr->getCurrentlyReadToken();

	if (currentToken->getTokenValue() == "true" ||
		currentToken->getTokenValue() == "false")
	{
		this->setIsValid(true);
	}

	else if (currentToken->getTokenValue() == "(") //Note:  We can't recurse here, since we are expecting the sequence of tokens "end" + "if"
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
		currentToken = this->parserPtr->readNextToken();
		this->dealWithExpression(motherNode, 0);
		this->setIsValid(true);

	}

	else if (currentToken->getTokenValue() == "-")
	{
		//Here, we need to recurse, since either a name or a number will be coming after it.
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
		++tokenCounter;
		currentToken = this->parserPtr->readNextToken();
		this->verifySyntaxCreateParseTree(tokenCounter, motherNode);
	}
	
	else if (currentToken->getTokenType() == "NUMBER")
	{
		//Well, now we have a number, so we create one.
		this->linkedMemberNonterminals.push_back(new Number(currentToken));
	}

	else if (currentToken->getTokenType() == "STRING_LITERAL")
	{
		//We have a string literal, so we create one.
		this->linkedMemberNonterminals.push_back(new StringLiteral(currentToken));
	}

	return;

	
}

ParseTreeNode* Factor::getNodePtr()
{
	return this;

}

void Factor::populateSearchResultsList(ParseTreeNode* motherNode)
{


	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}