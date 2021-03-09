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
	int    getNodeTokenLineNumber();
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	void populateLocalSearchResultsList() override;
	virtual ~TerminalNode() {};


protected:

	Token* token;
	
private:
	ParseTreeNode* getNodePtr() override;

};