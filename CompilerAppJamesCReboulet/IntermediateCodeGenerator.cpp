#include "IntermediateCodeGenerator.h"
#include "MainCompilerIntermediateCodeGenerationException.h"
#include "MainCompileErrorException.h"



IntermediateCodeGenerator::IntermediateCodeGenerator()
{
	try
	{
		this->init();
		if (this->getCompilerErrorsPresentFlag())
		{
			throw MainCompilerIntermediateCodeGenerationException();
		}

		//Make fstream a nullptr for now.
		else
		{
			this->parseTree->generateIntermediateCodeFromParseTree(nullptr);
		}
		
	}

	catch (MainCompileErrorException &e)
	{
		cout << endl << e.what() << endl;
		return;
	}

	catch (MainCompilerIntermediateCodeGenerationException &e)
	{
		cout << endl << e.what() << endl;
		
		
		return;
	}

}

IntermediateCodeGenerator::~IntermediateCodeGenerator()
{
	vector<ParseTreeNode*>* searchResultsList = nullptr;

	if (this->parseTree != nullptr)
	{
		searchResultsList = this->parseTree->getSearchResultsList(this->parseTree);



		for (unsigned int i = 0; i < searchResultsList->size(); ++i)
		{
			delete(searchResultsList->at(i));

		}
		
		
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
