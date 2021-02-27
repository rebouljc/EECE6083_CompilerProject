#pragma once
#include "ParseTreeNode.h"
class IfStatement : public ParseTreeNode
{
public:
	IfStatement(Parser* parser, ParseTreeNode* motherNode);
	void setIsValid(bool isValid) override { this->isValid = isValid; };
	bool getIsValid() override { return this->isValid; };
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	~IfStatement() {};

private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	void dealWithThenOrElse(ParseTreeNode* motherNode, int tokenCounter);
	void dealWithIf(ParseTreeNode* motherNode, int tokenCounter);
	vector<ParseTreeNode*> linkedMemberNonterminals;
	ParseTreeNode* getNodePtr() override;
	bool isValid = false;

};