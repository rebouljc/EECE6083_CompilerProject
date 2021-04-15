#pragma once
#include "ParseTreeNode.h"
class LoopStatement : public ParseTreeNode
{
public:
	LoopStatement(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr);
	void setIsValid(bool isValid) override { this->isValid = isValid; };
	bool getIsValid() override { return this->isValid; };
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	void setExpressionPtr(ParseTreeNode* expressionPtr) { this->expressionPtr = expressionPtr; };
	ParseTreeNode* getExpressionPtr() { return this->expressionPtr; };
	void setTokenToCompareLeftValue(ParseTreeNode* tokenToCompareLeft) { this->tokenToCompareLeft = tokenToCompareLeft; };
	ParseTreeNode* getTokenToCompareValue() { return this->tokenToCompareLeft; };

	void generateIntermediateCodeFromParseTree(ofstream* outputFileStream) override;
	
	~LoopStatement() {};

private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	void dealWithForHeader(ParseTreeNode* motherNode, int tokenCounter);
	void dealWithForBody(ParseTreeNode* motherNode, int tokenCounter);
	
	ParseTreeNode* getNodePtr() override;
	ParseTreeNode* expressionPtr = nullptr;
	ParseTreeNode* tokenToCompareLeft = nullptr;
	bool isValid = false;
	

};