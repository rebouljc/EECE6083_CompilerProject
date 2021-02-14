#pragma once
#include "ParseTreeNode.h"

class ProgramHeader : public ParseTreeNode
{
public:
	ProgramHeader(Parser* parser);
	ParseTreeNode* getNodePtr() override;
	void populateSearchResultsList(ParseTreeNode* motherNode) override;

private:
	void verifySyntaxCreateParseTree(int tokenCounter) override;
	vector<ParseTreeNode*> linkedMemberNonterminals;
	

};
