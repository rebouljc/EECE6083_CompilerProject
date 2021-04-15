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

	this->climbTreeAndVerifyTermOperationsAreCorrectlyDefined(this, false);

	bool relationPresentFlag = false;
	bool setRelationPresentFlag = false;
	this->climbTreeAndVerifyRelationOperationsAreCorrectlyDefined(this, false, relationPresentFlag, setRelationPresentFlag);

	bool expressionDefinedFlag = false;
	bool notWithParenthesesFlag = false;
	bool singleVariableIfLoopExpressionPresent = false;
	this->climbTreeAndVerifyExpressionOperationsAreCorrectlyDefined(this, false, expressionDefinedFlag, singleVariableIfLoopExpressionPresent);


}

void Number::generateIntermediateCodeFromParseTree(ofstream* outputFileStream)
{

}


ParseTreeNode* Number::getNodePtr()
{
	return this;

}

string Number::getNumberTokenType()
{
	
	return this->token->getTokenValue();
}

void Number::setNodeTokenIntegerDoubleNumberTokenValueToBoolean()
{
	this->token->setNodeTokenIntegerDoubleNumberTokenValueToBoolean();

	if (this->getConvertToNotValue())
	{
		if (this->token->getIntegerDoubleNumberTokenValue() == 0)
		{
			this->token->setDoubleNumberTokenValue(1);
			this->token->setTokenValue("true");
		}

		else
		{
			this->token->setDoubleNumberTokenValue(0);
			this->token->setTokenValue("false");
		}
	}
}

void Number::setNodeTokenIntegerDoubleNumberTokenValueToNotValue()
{
	this->token->setNodeTokenIntegerDoubleNumberTokenValueToNotValue();
}

double Number::getNodeTokenIntegerDoubleNumberTokenValue()
{
	return this->token->getIntegerDoubleNumberTokenValue();
}

void Number::populateSearchResultsList(ParseTreeNode* motherNode)
{
	motherNode->addToSearchResultsList(this->getNodePtr());
}

