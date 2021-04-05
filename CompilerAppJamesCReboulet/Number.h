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

	~Number() {};

private:

	bool bitwiseAndOrOperationDefined = false;
	bool readIntegerAsBooleanValueFlag = false;
	bool convertToNotValue = false;
	


};