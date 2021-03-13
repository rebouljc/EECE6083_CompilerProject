#include "LoopStatement.h"
#include "TerminalNode.h"
#include "Expression.h"
#include "AssignmentStatement.h"
#include "Statement.h"

LoopStatement::LoopStatement(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr)
{
	//Note: 3-13-2021: Added additional statement to set this node's parent node ptr, to enable reverse walking back up a tree.
	this->parentNodePtr = parentNodePtr;
	this->setParserPtr(parser);
	this->verifySyntaxCreateParseTree(0, motherNode);
}

void LoopStatement::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{    //Needs to be modified for program body.  Make it recursive to handle multiple declarations and statements.
	Token* currentToken = parserPtr->getCurrentlyReadToken();

	if (tokenCounter == 0 && currentToken->getTokenValue() == "for")
	{
		this->dealWithForHeader(motherNode, 0);
	}

	else if (tokenCounter == 1)
	{
		this->dealWithForBody(motherNode, 0);
	    
	}

	else if (currentToken->getTokenValue() == "end") //Note:  We can't recurse here, since we are expecting the sequence of tokens "end" + "if"
	{                                                //We can, but it would require using tokenCounter.  Easier just to add a couple of lines of code.
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
	}
	else if (tokenCounter == 3 && currentToken->getTokenValue() == "for")
	{
		
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
		this->setIsValid(true);
		return;
		

	}

	else
	{
		return;  //If you don't return here and the input is a ";" at the end of an assignment statement, this will blow up as well.
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
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
	}

	else if (currentToken->getTokenValue() == "(")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
	}
	else if (currentToken->getTokenValue() == ")")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
		return;
	}

	else if(tokenCounter == 2)
	{
		this->linkedMemberNonterminals.push_back(new AssignmentStatement(this->parserPtr, motherNode, this));
		bool isValid = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1)->getIsValid();
		if (!isValid)
		{
			//We throw an error here, since an expression is required.
			//Right now, we will return, though to prevent infinite recursion.
			this->linkedMemberNonterminals.pop_back();
			return;
		}

	}

	else if (currentToken->getTokenValue() == ";")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));

	}

	

	else if (tokenCounter == 4)
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

	else 
	{
		//We throw an error.  Return for now.
		return;
	}
	++tokenCounter;
	currentToken = this->parserPtr->readNextToken();
	this->dealWithForHeader(motherNode, tokenCounter);
	return;

}
void LoopStatement::dealWithForBody(ParseTreeNode* motherNode, int tokenCounter)
{
	Token* currentToken = this->parserPtr->getCurrentlyReadToken();
	//If we see an "end", just get out of here.  If we continue, it messes everything up
	if (currentToken->getTokenValue() == "end")
	{
		this->parserPtr->resetTokenReadIndexToPrevious();
		return;
	}

	this->linkedMemberNonterminals.push_back(new Statement(this->parserPtr, motherNode, this));
	bool isValid = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1)->getIsValid();
	if (!isValid)
	{
		this->linkedMemberNonterminals.pop_back();
		//If we ever get here, we reset the token
		
		return; //Here, we return at the first point that there is no valid statement, or we will infinitely recurse here.
	}

	currentToken = this->parserPtr->readNextToken();
	if (currentToken->getTokenValue() == ";")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
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


	for (unsigned int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}
