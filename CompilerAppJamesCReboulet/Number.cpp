#include "Number.h"

Number::Number(Token* token)
{
	this->token = token;

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

void Number::populateLocalSearchResultsList()
{
	this->addToSearchResultsList(this->getNodePtr());

}
