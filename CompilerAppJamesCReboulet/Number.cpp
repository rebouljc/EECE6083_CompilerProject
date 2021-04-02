#include "Number.h"

Number::Number(Token* token, ParseTreeNode* parentNodePtr)
{
	//Note: 3-13-2021: Added additional statement to set this node's parent node ptr, to enable reverse walking back up a tree.
	this->parentNodePtr = parentNodePtr;
	this->token = token;
	this->climbTreeAndVerifyArrayIndices(this);
	this->climbTreeAndVerifyArithmeticOperationsAreCorrectlyDefined(this, false);
	
	//1) Add method called:
	//this->climbTreeAndVerifyTermOperationsAreCorrectlyDefined(this,false).
	//Take this->climbTreeAndVerifyArithmeticOperationsAreCorrectlyDefined(this, false) and modify it.
	//2) All previous methods can be used theoretically, as far as I can tell, unless there is something 
	//   specific about those methods that only applies to arithmetic operations.  


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

