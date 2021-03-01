#include "StringLiteral.h"

StringLiteral::StringLiteral(Token* token)
{
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