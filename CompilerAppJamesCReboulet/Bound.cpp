#include "Bound.h"
#include "TerminalNode.h"
#include "Number.h"

Bound::Bound(Token* token, Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr)
{
	//Note: 3-13-2021: Added additional statement to set this node's parent node ptr, to enable reverse walking back up a tree.
	this->parentNodePtr = parentNodePtr;
	this->token = token;
	this->setParserPtr(parser);
	this->programNode_motherNode = motherNode;
	this->verifySyntaxCreateParseTree(0, motherNode);
	
}

void Bound::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{
	
	if (this->token->getTokenType() == "NUMBER")
	{
		this->linkedMemberNonterminals.push_back(new Number(this->token, this));
	}

	else
	{
		//Throw an exception or generate an error.  This is a problem.
	}

}

ParseTreeNode* Bound::getNodePtr()
{
	return this;

}

void Bound::populateSearchResultsList(ParseTreeNode* motherNode)
{


	for (unsigned int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}


void Bound::checkArrayIndexWithinRange(ParseTreeNode numberNode)
{

}

