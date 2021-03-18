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
	~Identifier() {};


private:

	string identifierType;
	bool isValidDeclaration = false;


};