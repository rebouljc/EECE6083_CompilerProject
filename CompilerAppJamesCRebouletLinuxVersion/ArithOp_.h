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
	

	ParseTreeNode* getNodePtr() override;
	bool isValid = false;
	
	

};