#pragma once
#include "ParseTreeNode.h"
#include "Token.h"

class TerminalNode : public ParseTreeNode
{
public:
	TerminalNode(Token* token);
	string getNodeTokenType();
	string getNodeTokenValue();
	double getNodeTokenIntegerDoubleNumberTokenValue();
	int    getNodeTokenLineNumber();
	ParseTreeNode*  getNodePtr() override;
	void populateSearchResultsList(ParseTreeNode* motherNode) override;

private:

	Token* token;


};