#pragma once
#include "Token.h"
#include "TerminalNode.h"

class StringLiteral : public TerminalNode
{
public:
	StringLiteral(Token* token, ParseTreeNode* parentNodePtr);
	ParseTreeNode* getNodePtr() override;
	void populateSearchResultsList(ParseTreeNode* motherNode) override;

	void setBitwiseAndOrOperationDefinedFlagValue(bool flagValue) { this->bitwiseAndOrOperationDefined = flagValue; };
	bool getBitwiseAndOrOperationDefinedFlagValue() { return this->bitwiseAndOrOperationDefined; };

	void setRelationPresentFlag(bool flagValue) { this->relationPresentFlag = flagValue; };
	bool getRelationPresentFlagValue() { return this->relationPresentFlag; };

	void setNoStringsAllowedValue(bool flagValue) { this->noStringsAllowedFlag = flagValue; };
	bool getNoStringsAllowedFlagValue() { return this->noStringsAllowedFlag; };

	//And the flags keep waving!  More flags.  Now, the if_statement/Loop flags. 
	//The kicker is that if you set one of them incorrectly, the whole application will be destroyed :).  

	void setSingleVariableIfLoopExpressionFlag(bool flagValue) { this->singleVariableIfOrLoopExpressionFlag = flagValue; };
	bool getSingleVariableIfLoopExpressionFlag() { return this->singleVariableIfOrLoopExpressionFlag; };

	~StringLiteral() {};

private:

	bool bitwiseAndOrOperationDefined = false;
	bool relationPresentFlag = false;
	bool noStringsAllowedFlag = false;
	bool singleVariableIfOrLoopExpressionFlag = false;

};