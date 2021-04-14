#pragma once
#include "ParseTreeNode.h"
#include "Token.h"
#include <string>

#define OUT 0

class TerminalNode : public ParseTreeNode
{
public:
	TerminalNode();
	TerminalNode(Token* token, ParseTreeNode* parentNodePtr);
	string getNodeTokenType();
	string getNodeTokenValue();
	void setNodeTokenValue(std:: string value);
	int    getNodeTokenLineNumber();
	void populateSearchResultsList(ParseTreeNode* motherNode) override;

	void generateIntermediateCodeFromParseTree(ifstream* outputFileStream) override;
	
	virtual ~TerminalNode() {};


protected:
	
	Token* token;
	
private:
	ParseTreeNode* getNodePtr() override;


	bool parenthesesPresentFlag = false;


};