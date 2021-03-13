#include "IntermediateCodeGenerator.h"


IntermediateCodeGenerator::IntermediateCodeGenerator()
{
	this->init();
}

IntermediateCodeGenerator::~IntermediateCodeGenerator()
{
	vector<ParseTreeNode*>* searchResultsList = this->parseTree->getSearchResultsList(this->parseTree);
	//Try this just for fun to test local populate search results list;
	
	for (unsigned int i = 0; i < searchResultsList->size(); ++i)
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
