#include "LoopStatement.h"
#include "TerminalNode.h"
#include "Expression.h"
#include "AssignmentStatement.h"
#include "Statement.h"

LoopStatement::LoopStatement(Parser* parser, ParseTreeNode* motherNode)
{
	this->setParserPtr(parser);
	this->verifySyntaxCreateParseTree(0, motherNode);
}

void LoopStatement::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{    //Needs to be modified for program body.  Make it recursive to handle multiple declarations and statements.
	Token* currentToken = parserPtr->getCurrentlyReadToken();

	if (currentToken->getTokenValue() == "for")
	{
		this->dealWithForHeader(motherNode, 0);
	}

	else if (tokenCounter == 1)
	{
		this->dealWithForBody(motherNode, 0);
	}

	else if (currentToken->getTokenValue() == "end") //Note:  We can't recurse here, since we are expecting the sequence of tokens "end" + "if"
	{                                                //We can, but it would require using tokenCounter.  Easier just to add a couple of lines of code.
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
		currentToken = this->parserPtr->readNextToken();

		if (currentToken->getTokenValue() == "for")
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

void LoopStatement::dealWithForHeader(ParseTreeNode* motherNode, int tokenCounter)
{
	Token* currentToken = this->parserPtr->getCurrentlyReadToken();

	if (currentToken->getTokenValue() == "for")
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

	else if(tokenCounter == 3)
	{
		this->linkedMemberNonterminals.push_back(new AssignmentStatement(this->parserPtr, motherNode));
		bool isValid = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);
		if (!isValid)
		{
			//We throw an error here, since an expression is required.
			//Right now, we will return, though to prevent infinite recursion.
			return;
		}

	}

	else if (currentToken->getTokenValue() == ";")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));

	}

	else if (tokenCounter == 4 && currentToken->getTokenValue() != ";")
	{
		//We throw an error.  Return for now.
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
	this->dealWithForHeader(motherNode, tokenCounter);
	return;

}
void LoopStatement::dealWithForBody(ParseTreeNode* motherNode, int tokenCounter)
{
	Token* currentToken = this->parserPtr->getCurrentlyReadToken();

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
	
	++tokenCounter;
	currentToken = this->parserPtr->readNextToken();
	this->dealWithForBody(motherNode, tokenCounter);
	return;

}

ParseTreeNode* LoopStatement::getNodePtr()
{
	return this;

}

void LoopStatement::populateSearchResultsList(ParseTreeNode* motherNode)
{


	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}