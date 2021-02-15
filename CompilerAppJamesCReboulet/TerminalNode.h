#pragma once
#include "ParseTreeNode.h"
#include "Token.h"

class TerminalNode : public ParseTreeNode
{
public:
	TerminalNode(Token* token);
	TerminalNode(Token* token, ParseTreeNode* motherNode, string identifierType);
	string getNodeTokenType();
	string getNodeTokenValue();
	string getNodeSymbolIdentifierType();
	double getNodeTokenIntegerDoubleNumberTokenValue();
	int    getNodeTokenLineNumber();
	ParseTreeNode*  getNodePtr() override;
	void populateSearchResultsList(ParseTreeNode* motherNode) override;


private:

	Token* token;
	string identifierType;


};