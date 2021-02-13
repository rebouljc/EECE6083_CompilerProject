#pragma once
#include "ParseTreeNode.h"

class ProgramHeader : public ParseTreeNode
{
public:
	ProgramHeader(Parser* parser);

private:
	void verifySyntaxCreateParseTree() override;
	vector<ParseTreeNode*> linkedMemberNonterminals;


};
