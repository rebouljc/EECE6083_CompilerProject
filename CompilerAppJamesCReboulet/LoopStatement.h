#pragma once
#include "ParseTreeNode.h"
class LoopStatement : public ParseTreeNode
{
public:
	LoopStatement(Parser* parser, ParseTreeNode* motherNode);
	void setIsValid(bool isValid) override { this->isValid = isValid; };
	bool getIsValid() override { return this->isValid; };
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	~LoopStatement() {};

private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	void dealWithForHeader(ParseTreeNode* motherNode, int tokenCounter);
	void dealWithForBody(ParseTreeNode* motherNode, int tokenCounter);
	vector<ParseTreeNode*> linkedMemberNonterminals;
	ParseTreeNode* getNodePtr() override;
	bool isValid = false;

};