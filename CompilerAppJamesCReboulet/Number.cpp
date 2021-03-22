#include "Number.h"

Number::Number(Token* token, ParseTreeNode* parentNodePtr)
{
	//Note: 3-13-2021: Added additional statement to set this node's parent node ptr, to enable reverse walking back up a tree.
	this->parentNodePtr = parentNodePtr;
	this->token = token;
	this->climbTreeAndVerifyArrayIndices(this);

}

ParseTreeNode* Number::getNodePtr()
{
	return this;

}

string Number::getNumberTokenType()
{
	
	return this->token->getTokenValue();
}

double Number::getNodeTokenIntegerDoubleNumberTokenValue()
{
	return this->token->getIntegerDoubleNumberTokenValue();
}

void Number::populateSearchResultsList(ParseTreeNode* motherNode)
{
	motherNode->addToSearchResultsList(this->getNodePtr());
}

