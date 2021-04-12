#pragma once
#include "Token.h"
#include "TerminalNode.h"

class Number : public TerminalNode
{
public:
	Number(Token* token, ParseTreeNode* parentNodePtr);
	double getNodeTokenIntegerDoubleNumberTokenValue();
	void setNodeTokenIntegerDoubleNumberTokenValueToBoolean();
	void setNodeTokenIntegerDoubleNumberTokenValueToNotValue();
	ParseTreeNode* getNodePtr() override;
	string getNumberTokenType();
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	void setBitwiseAndOrOperationDefinedFlagValue(bool flagValue) { this->bitwiseAndOrOperationDefined = flagValue; };
	bool getBitwiseAndOrOperationDefinedFlagValue() { return this->bitwiseAndOrOperationDefined; };

	void setreadIntegerAsBooleanValueFlagValue(bool flagValue) { this->readIntegerAsBooleanValueFlag = flagValue; };
	bool getreadIntegerAsBooleanValueFlagValue() { return this->readIntegerAsBooleanValueFlag; };

	void setConvertToNotValue(bool flagValue) { this->convertToNotValue = flagValue; };
	bool getConvertToNotValue() { return this->convertToNotValue; };

	void setRelationPresentFlag(bool flagValue) { this->relationPresentFlag = flagValue; };
	bool getRelationPresentFlagValue() { return this->relationPresentFlag; };

	void setSingleVariableIfLoopExpressionFlag(bool flagValue) { this->singleVariableIfOrLoopExpressionFlag = flagValue; };
	bool getSingleVariableIfLoopExpressionFlag() { return this->singleVariableIfOrLoopExpressionFlag; };

	~Number() {};

private:

	bool bitwiseAndOrOperationDefined = false;
	bool readIntegerAsBooleanValueFlag = false;
	bool convertToNotValue = false;
	bool relationPresentFlag = false;
	bool singleVariableIfOrLoopExpressionFlag = false;


};