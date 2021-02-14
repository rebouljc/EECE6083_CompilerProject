#pragma once

#include "ParseTreeNode.h"

class Program: public ParseTreeNode
{
public:
	Program(Parser* parser);
	ParseTreeNode* getNodePtr() override;
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	
	
private:
	void verifySyntaxCreateParseTree() override;
	vector<ParseTreeNode*> linkedMemberNonterminals;
	
	

};