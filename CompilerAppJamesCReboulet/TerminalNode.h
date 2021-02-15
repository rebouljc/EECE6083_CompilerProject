#pragma once
#include "ParseTreeNode.h"
#include "Token.h"

class TerminalNode : public ParseTreeNode
{
public:
	TerminalNode();
	TerminalNode(Token* token);
	
	string getNodeTokenType();
	string getNodeTokenValue();
	virtual string getNodeSymbolIdentifierType() { return NULL; };
    double getNodeTokenIntegerDoubleNumberTokenValue();
	int    getNodeTokenLineNumber();
	ParseTreeNode*  getNodePtr() override;
	void populateSearchResultsList(ParseTreeNode* motherNode) override;


protected:

	Token* token;
	


};