#include "IfStatement.h"
#include "Expression.h"
#include "Identifier.h"
#include "Statement.h"
#include "TerminalNode.h"


IfStatement::IfStatement(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr)
{
	//Note: 3-13-2021: Added additional statement to set this node's parent node ptr, to enable reverse walking back up a tree.
	this->parentNodePtr = parentNodePtr;
	this->setParserPtr(parser);
	this->programNode_motherNode = motherNode;
	this->verifySyntaxCreateParseTree(0, motherNode);
	
}
void IfStatement::dealWithThenOrElse(ParseTreeNode* motherNode, int tokenCounter)
{
	Token* currentToken = this->parserPtr->getCurrentlyReadToken();

	if (currentToken->getTokenValue() == "then" || currentToken->getTokenValue() == "else")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
	}

	else if (tokenCounter >= 1)
	{
		if (currentToken->getTokenValue() != "end")
		{
			this->linkedMemberNonterminals.push_back(new Statement(this->parserPtr, motherNode, this));

			bool isValid = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1)->getIsValid();
			if (!isValid)
			{
				this->linkedMemberNonterminals.pop_back();
				return; //Here, we return at the first point that there is no valid statement, or we will infinitely recurse here.
			}

			currentToken = this->parserPtr->readNextToken();
			if (currentToken->getTokenValue() == ";")
			{
				this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
			}
		}
		else
		{
			//We need to give back the token, so that the if-statement can begin with "end" instead of "if" and mess things up.
			this->parserPtr->resetTokenReadIndexToPrevious();
			return;
		}
	}

	else
	{
		return;
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
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
	}

	else if (currentToken->getTokenValue() == "(")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
	}
	else if (currentToken->getTokenValue() == ")")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
		//We have to read the next token, so we don't mess up the "then" portion when this returns back
		//to the verifySyntaxCreateParseTreeMethod.
		return;
	}

	else
	{
		this->linkedMemberNonterminals.push_back(new Expression(this->parserPtr, motherNode, this));
		bool isValid = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1)->getIsValid();
		if (!isValid)
		{
			//We throw an error here, since an expression is required.
			//Right now, we will return, though to prevent infinite recursion.
			this->linkedMemberNonterminals.pop_back();
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

	else if (currentToken->getTokenValue() == "then")
	{
		
		this->dealWithThenOrElse(motherNode, 0);
		
		
	}

	else if (currentToken->getTokenValue() == "else")
	{
		
		this->dealWithThenOrElse(motherNode, 0);
		++tokenCounter;
	}

	else if (currentToken->getTokenValue() == "end") //Note:  We can't recurse here, since we are expecting the sequence of tokens "end" + "if"
	{
		
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
		currentToken = this->parserPtr->readNextToken();

		if (currentToken->getTokenValue() == "if")
		{
			currentToken = parserPtr->getCurrentlyReadToken();
			this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
			this->setIsValid(true);
			return;
		}

	}

	//Else, EXPLODE!  This is what happens when you forget to add an else{} in this recursive method, return statement.  Need to add it.
	//This statement can be reached, even if it is not a valid if-statement, because the method is always tested for each program, regardless if it is correct.

	else
	{
		return;
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


	for (unsigned int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}
