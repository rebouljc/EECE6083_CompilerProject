#pragma once
#include "ParseTreeNode.h"

class Declaration : public ParseTreeNode
{
public:
	Declaration(Parser* parser, ParseTreeNode* motherNode);

	void populateSearchResultsList(ParseTreeNode* motherNode) override;

private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	vector<ParseTreeNode*> linkedMemberNonterminals;
	ParseTreeNode* getNodePtr() override;

};