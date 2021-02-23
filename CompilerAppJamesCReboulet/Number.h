#pragma once
#include "Token.h"
#include "TerminalNode.h"

class Number : public TerminalNode
{
public:
	Number(Token* token);
	double getNodeTokenIntegerDoubleNumberTokenValue();
	ParseTreeNode* getNodePtr() override;
	string getNumberTokenType();
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	~Number() {};

private:

	


};