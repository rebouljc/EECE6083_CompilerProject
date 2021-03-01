#pragma once
#include "Token.h"
#include "TerminalNode.h"

class StringLiteral : public TerminalNode
{
public:
	StringLiteral(Token* token);
	ParseTreeNode* getNodePtr() override;
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	~StringLiteral() {};

private:




};