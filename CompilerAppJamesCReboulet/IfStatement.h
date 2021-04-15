#pragma once
#include "ParseTreeNode.h"
class IfStatement : public ParseTreeNode
{
public:
	IfStatement(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr);
	void setIsValid(bool isValid) override { this->isValid = isValid; };
	bool getIsValid() override { return this->isValid; };
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	void setExpressionPtr(ParseTreeNode* expressionPtr) { this->expressionPtr = expressionPtr; };
	ParseTreeNode* getExpressionPtr() { return this->expressionPtr; };
	void setTokenToCompareLeftValue(ParseTreeNode* tokenToCompareLeft) { this->tokenToCompareLeft = tokenToCompareLeft; };
	ParseTreeNode* getTokenToCompareValue() { return this->tokenToCompareLeft; };

	void generateIntermediateCodeFromParseTree(ofstream* outputFileStream) override;

	~IfStatement() {};
	

private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	void dealWithThenOrElse(ParseTreeNode* motherNode, int tokenCounter);
	void dealWithIf(ParseTreeNode* motherNode, int tokenCounter);
	ParseTreeNode* getNodePtr() override;
	bool isValid = false;
	ParseTreeNode* expressionPtr = nullptr;
	ParseTreeNode* tokenToCompareLeft = nullptr;
	

};