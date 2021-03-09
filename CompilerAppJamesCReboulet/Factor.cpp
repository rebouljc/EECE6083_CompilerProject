#include "Factor.h"
#include "TerminalNode.h"
#include "Expression.h"
#include "Number.h"
#include "StringLiteral.h"
#include "Name.h"
#include "ProcedureCall.h"

//2-23-2021: Code needs to be modified.  This is type mark code.
Factor::Factor(Parser* parser, ParseTreeNode* motherNode)
{
	this->setParserPtr(parser);
	this->verifySyntaxCreateParseTree(0, motherNode);
}

void Factor::dealWithExpression(ParseTreeNode* motherNode, int tokenCounter)
{
	Token* currentToken = parserPtr->getCurrentlyReadToken();
	printf("\nFactor_CurrentToken = %s", currentToken->getTokenValue().c_str());
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
	printf("\nFactor_CurrentToken = %s", currentToken->getTokenValue().c_str());

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
		this->setIsValid(true);
	}

	else if (currentToken->getTokenType() == "STRING_LITERAL")
	{
		//We have a string literal, so we create one.
		this->linkedMemberNonterminals.push_back(new StringLiteral(currentToken));
		this->setIsValid(true);

	}

	else if (currentToken->getTokenType() == "IDENTIFIER")
	{
		this->linkedMemberNonterminals.push_back(new Name(this->parserPtr, motherNode));
		ParseTreeNode* lastNode = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);
		bool stolenToken = false;
		if (!lastNode->getIsValid())
		{
			this->linkedMemberNonterminals.pop_back();
			stolenToken = true;
		
			//this->parserPtr->resetTokenReadIndexToPrevious();  //Try giving it back. 3/1/2021.  Here lies the issue.  Fix this!.
															   //Somewhere along the line, there is some unneccessary recursion going on.
			 //We definitely do not have a parameterList if there is no <parameter>
		}
		else
		{
			this->setIsValid(true);
			//If Name is valid, then procedure call is not valid and we need to return or else
			//Procedure_Call will be tested and it could be valid.
			return;
		}
		if (stolenToken)
		{
			this->linkedMemberNonterminals.push_back(new ProcedureCall(this->parserPtr, motherNode, currentToken));
		}
		else
		{
			this->linkedMemberNonterminals.push_back(new ProcedureCall(this->parserPtr, motherNode));
		}
		lastNode = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);
		if (!lastNode->getIsValid())
		{
			this->linkedMemberNonterminals.pop_back();
			//this->parserPtr->resetTokenReadIndexToPrevious();  //Try giving it back. 3/1/2021.  Here lies the issue.  Fix this!.
			                                                   //Somewhere along the line, there is some unneccessary recursion going on.
			return;  //We definitely do not have a parameterList if there is no <parameter>
		}
		else
		{
			this->setIsValid(true);
		}

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

void Factor::populateLocalSearchResultsList()
{
	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList();
	}

}