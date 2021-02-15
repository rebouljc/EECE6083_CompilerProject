#include "Program.h"
#include "ProgramHeader.h"


Program::Program(Parser* parser)
{
	this->setParserPtr(parser);
	this->verifySyntaxCreateParseTree(0, (ParseTreeNode*) this);
}

void Program::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{
	//always make sure to pass the parser ptr.
	//create a program header.
	this->linkedMemberNonterminals.push_back(new ProgramHeader(this->parserPtr, motherNode)); //If any of these operations fail, an exception will be thrown and 
	                                                                              //this method won't complete.  At the first instance of failure,
	                                                                              //exceptions will be thrown, unless we can detect and recover from all
	                                                                              //failures and throw one giant exception at the end with all of the errors.


}
ParseTreeNode* Program::getNodePtr()
{
	return this;
}

void Program::populateSearchResultsList(ParseTreeNode* motherNode)
{
	motherNode = (ParseTreeNode*)(this);

	

	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	this->searchResultsList.push_back(this->getNodePtr());
}
