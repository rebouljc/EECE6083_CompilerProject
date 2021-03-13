#include "StringLiteral.h"

StringLiteral::StringLiteral(Token* token, ParseTreeNode* parentNodePtr)
{
	//Note: 3-13-2021: Added additional statement to set this node's parent node ptr, to enable reverse walking back up a tree.
	this->parentNodePtr = parentNodePtr;
	this->token = token;

}

ParseTreeNode* StringLiteral::getNodePtr()
{
	return this;

}

void StringLiteral::populateSearchResultsList(ParseTreeNode* motherNode)
{
	motherNode->addToSearchResultsList(this->getNodePtr());
}
