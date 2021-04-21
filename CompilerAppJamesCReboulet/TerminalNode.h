#pragma once
#include "ParseTreeNode.h"
#include "Token.h"
#include <string>

#define OUT 0

class TerminalNode : public ParseTreeNode
{
public:
	TerminalNode();
	TerminalNode(Token* token, ParseTreeNode* parentNodePtr, ParseTreeNode* motherNodePtr);
	string getNodeTokenType();
	string getNodeTokenValue();
	void setNodeTokenValue(std:: string value);
	void setNodeTokenType(std::string type);
	int    getNodeTokenLineNumber();
	void populateSearchResultsList(ParseTreeNode* motherNode) override;

	void generateIntermediateCodeFromParseTree(ofstream* outputFileStream, vector<ParseTreeNode*>* declSymbolTablePtr) override;
	
	virtual ~TerminalNode() {};


protected:
	
	Token* token;
	
private:
	ParseTreeNode* getNodePtr() override;


	bool parenthesesPresentFlag = false;


};