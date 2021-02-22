#include "IntermediateCodeGenerator.h"


IntermediateCodeGenerator::IntermediateCodeGenerator()
{
	this->init();
}

IntermediateCodeGenerator::~IntermediateCodeGenerator()
{
	vector<ParseTreeNode*>* searchResultsList = parseTree->getSearchResultsList(parseTree);
	for (int i = 0; i < searchResultsList->size(); ++i)
	{
		delete(searchResultsList->at(i));

	}
}

void IntermediateCodeGenerator::init()
{
	((Parser*)(this))->init();
}

void IntermediateCodeGenerator::setParseTreePtr(ParseTreeNode* parseTree)
{
	this->parseTree = parseTree;
}