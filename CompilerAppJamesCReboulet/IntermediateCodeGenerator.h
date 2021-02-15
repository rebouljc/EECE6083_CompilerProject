#pragma once
#include "ParseTreeNode.h"

class IntermediateCodeGenerator
{
public:
	IntermediateCodeGenerator(ParseTreeNode*);
private:
	ParseTreeNode* parseTree;
};