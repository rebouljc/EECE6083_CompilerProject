#include "IntermediateCodeGenerator.h"
#include "MainCompileErrorException.h"


IntermediateCodeGenerator::IntermediateCodeGenerator()
{
	
	this->init();
	

}

IntermediateCodeGenerator::~IntermediateCodeGenerator()
{
	vector<ParseTreeNode*>* searchResultsList = this->parseTree->getSearchResultsList(this->parseTree);
	
	
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
