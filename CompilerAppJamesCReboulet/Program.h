#pragma once

#include "ParseTreeNode.h"

class Program: public ParseTreeNode
{
public:
	Program(Parser* parser);
	
private:
	void verifySyntaxCreateParseTree() override;
	vector<ParseTreeNode*> linkedMemberNonterminals;
	

};