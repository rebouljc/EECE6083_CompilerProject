#pragma once
#include "ParseTreeNode.h"

class ProgramHeader : public ParseTreeNode
{
public:
	ProgramHeader(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr);
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	~ProgramHeader() {};
	

private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	vector<ParseTreeNode*> linkedMemberNonterminals;
	ParseTreeNode* getNodePtr() override;

};
