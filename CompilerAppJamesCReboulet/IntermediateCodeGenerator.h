#pragma once
#include "ParseTreeNode.h"

class IntermediateCodeGenerator
{
public:
	IntermediateCodeGenerator(ParseTreeNode*);
	~IntermediateCodeGenerator() {};
private:
	ParseTreeNode* parseTree;
};