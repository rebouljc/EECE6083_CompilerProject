#pragma once
#include "ParseTreeNode.h"
class ArithOp_ : public ParseTreeNode
{
public:
	ArithOp_(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr);
	void setIsValid(bool isValid) override { this->isValid = isValid; };
	bool getIsValid() override { return this->isValid; };
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	~ArithOp_() {};
	

private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	void dealWithForHeader(ParseTreeNode* motherNode, int tokenCounter);
	void dealWithForBody(ParseTreeNode* motherNode, int tokenCounter);

	ParseTreeNode* getNodePtr() override;
	bool isValid = false;
	
	

};