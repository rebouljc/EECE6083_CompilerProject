#pragma once
#include "ParseTreeNode.h"
#include "Token.h"
#include "TerminalNode.h"

class Identifier : public TerminalNode
{
public:
	Identifier(Token* token, ParseTreeNode* motherNode, string identifierType);
	string getNodeSymbolIdentifierType();
	ParseTreeNode* getNodePtr() override;
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	~Identifier() {};

private:

	string identifierType;


};