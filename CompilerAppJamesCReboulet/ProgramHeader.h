#pragma once
#include "ParseTreeNode.h"

class ProgramHeader : public ParseTreeNode
{
public:
	ProgramHeader(Parser* parser, ParseTreeNode* motherNode);
	ParseTreeNode* getNodePtr() override;
	void populateSearchResultsList(ParseTreeNode* motherNode) override;

private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	vector<ParseTreeNode*> linkedMemberNonterminals;
	

};
