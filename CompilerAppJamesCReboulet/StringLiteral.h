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

	~StringLiteral() {};

private:

	bool bitwiseAndOrOperationDefined = false;
	bool relationPresentFlag = false;
	bool noStringsAllowedFlag = false;


};