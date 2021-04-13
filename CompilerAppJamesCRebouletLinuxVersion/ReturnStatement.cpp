#include "ReturnStatement.h"
#include "TerminalNode.h"
#include "Expression.h"

ReturnStatement::ReturnStatement(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr)
{
	//Note: 3-13-2021: Added additional statement to set this node's parent node ptr, to enable reverse walking back up a tree.
	this->parentNodePtr = parentNodePtr;
	this->setParserPtr(parser);
	this->programNode_motherNode = motherNode;
	this->verifySyntaxCreateParseTree(0, motherNode);
	
}

void ReturnStatement::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{   //Needs to be modified for program body.  Make it recursive to handle multiple declarations and statements.

	Token* currentToken = this->parserPtr->getCurrentlyReadToken();
	if (currentToken->getTokenValue() == "return")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
	}
	else if (   !this->linkedMemberNonterminals.empty() &&
		        dynamic_cast<TerminalNode*>(this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1)) != nullptr
		    )
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

		this->setIsValid(true);
	}

	else
	{
		if (this->isValid) //This means that we have recursed once again and read the next token, so we have to give it back
		{
			this->parserPtr->resetTokenReadIndexToPrevious();
		}
		return;
	}
	++tokenCounter;
	currentToken = this->parserPtr->readNextToken();
	this->verifySyntaxCreateParseTree(tokenCounter, motherNode);


}

ParseTreeNode* ReturnStatement::getNodePtr()
{
	return this;

}

void ReturnStatement::populateSearchResultsList(ParseTreeNode* motherNode)
{


	for (unsigned int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}
