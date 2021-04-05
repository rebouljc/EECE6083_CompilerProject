#pragma once
#include "ParseTreeNode.h"
#include "Token.h"
#include "TerminalNode.h"

class Identifier : public TerminalNode
{
public:

	Identifier(Token* token, ParseTreeNode* motherNode, string identifierType, ParseTreeNode* parentNodePtr);
	Identifier(Token* token, ParseTreeNode* motherNode, string identifierType, ParseTreeNode* parentNodePtr, bool isValidDeclaration);
	string getNodeSymbolIdentifierType();
	ParseTreeNode* getNodePtr() override;
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	void setIdentifierTypeToGlobal();
	bool getIdentifierIsValidDeclaration() { return this->isValidDeclaration; };
	void setNumberPtrValue(ParseTreeNode* numberNode);
	ParseTreeNode* getNumberPtrValue();
	//Flag methods
	void setBitwiseAndOrOperationDefinedFlagValue(bool flagValue) { this->bitwiseAndOrOperationDefined = flagValue; };
	bool getBitwiseAndOrOperationDefinedFlagValue() { return this->bitwiseAndOrOperationDefined; };

	void setreadIntegerAsBooleanValueFlagValue(bool flagValue) { this->readIntegerAsBooleanValueFlag = flagValue; };
	bool getreadIntegerAsBooleanValueFlagValue() { return this->readIntegerAsBooleanValueFlag; };

	void setConvertToNotValue(bool flagValue) { this->convertToNotValue= flagValue; };
	bool getConvertToNotValue() { return this->convertToNotValue; };
	~Identifier() {};


private:

	string identifierType;
	bool isValidDeclaration = false;
	ParseTreeNode* numberPtr;
	bool bitwiseAndOrOperationDefined = false;
	bool readIntegerAsBooleanValueFlag = false;
	bool convertToNotValue = false;


};