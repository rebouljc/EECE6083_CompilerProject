#include "Destination.h"
#include "TerminalNode.h"
#include "Identifier.h"
#include "Expression.h"

//2-23-2021: Code needs to be modified.  This is type mark code.

Destination::Destination(Parser* parser, ParseTreeNode* motherNode)
{
	this->setParserPtr(parser);
	this->verifySyntaxCreateParseTree(0, motherNode);
}

void Destination::createEnumList(ParseTreeNode* motherNode)
{
	/*
	Token* currentToken = this->parserPtr->getCurrentlyReadToken();
	//Create the new identifier and check its validity.
	if (currentToken->getTokenValue() == "{")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
	}

	if (currentToken->getTokenType() == "IDENTIFIER")
	{
		this->linkedMemberNonterminals.push_back(new Identifier(currentToken, motherNode, "GLOBAL"));
	}

	else if (currentToken->getTokenValue() == ",")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
	}

	else if (currentToken->getTokenValue() == "}")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
		return;
	}
	else
	{
		return;  //Here, again, we will have to throw some type of syntax error, depending on what is missing.
				 //We need to prevent infinite recursion here.
	}
	currentToken = this->parserPtr->readNextToken();
	this->createEnumList(motherNode);
	*/
}

void Destination::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{   
	//Defining as of 2/26/2021
	Token* currentToken = parserPtr->getCurrentlyReadToken();
	if (currentToken->getTokenType() == "IDENTIFIER")
	{
		this->linkedMemberNonterminals.push_back(new Identifier(currentToken, motherNode, "GLOBAL"));
		//recurse
		++tokenCounter;
		currentToken = this->parserPtr->readNextToken();
		this->verifySyntaxCreateParseTree(tokenCounter, motherNode);
	}

	else if (tokenCounter == 1)
	{
		//The option of having an expression here is optional, so if we don't have an expression, we need to get rid of the pointer
		//to the class within the parse tree, since it makes things more confusing.  First we have to add it to the tree and then check.

		this->linkedMemberNonterminals.push_back(new Expression(this->parserPtr,motherNode));
		bool isValid = !this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1)->getIsValid();
		if (!isValid)
		{
			this->linkedMemberNonterminals.pop_back();
		}

	}

	//Otherwise, we return.
	return;

	
	
}

ParseTreeNode* Destination::getNodePtr()
{
	return this;

}

void Destination::populateSearchResultsList(ParseTreeNode* motherNode)
{


	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}