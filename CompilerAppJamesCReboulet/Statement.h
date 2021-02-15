#pragma once
#include "ParseTreeNode.h"

class Statement : public ParseTreeNode
{
public:
	Statement(Parser* parser, ParseTreeNode* motherNode);

	void populateSearchResultsList(ParseTreeNode* motherNode) override;

private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	vector<ParseTreeNode*> linkedMemberNonterminals;
	ParseTreeNode* getNodePtr() override;

};