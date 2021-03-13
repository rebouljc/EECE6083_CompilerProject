#pragma once
#include "ParseTreeNode.h"

class IntermediateCodeGenerator: public Parser
{
public:
	IntermediateCodeGenerator();
	void init();
	void setParseTreePtr(ParseTreeNode* parseTree);
	~IntermediateCodeGenerator();

private:
	ParseTreeNode* parseTree;

};