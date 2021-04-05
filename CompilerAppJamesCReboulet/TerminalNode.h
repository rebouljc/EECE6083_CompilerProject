#pragma once
#include "ParseTreeNode.h"
#include "Token.h"

#define OUT 0

class TerminalNode : public ParseTreeNode
{
public:
	TerminalNode();
	TerminalNode(Token* token, ParseTreeNode* parentNodePtr);
	string getNodeTokenType();
	string getNodeTokenValue();
	int    getNodeTokenLineNumber();
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
#ifndef OUT
	void setParenthesesPresentFlag(bool flagValue);

	bool getParenthesesPresentFlag() { return this->parenthesesPresentFlag; };
#endif
	virtual ~TerminalNode() {};


protected:

	Token* token;
	
private:
	ParseTreeNode* getNodePtr() override;


#ifndef OUT
	bool parenthesesPresentFlag = false;
#endif

};