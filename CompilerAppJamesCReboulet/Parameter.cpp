#include "Parameter.h"
#include "VariableDeclaration.h"

Parameter::Parameter(Parser* parser, ParseTreeNode* motherNode)
{
	this->setParserPtr(parser); 
	this->verifySyntaxCreateParseTree(0, motherNode);
}

void Parameter::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{  
	//dynamic_cast takes more work.  Do static_cast.
	this->linkedMemberNonterminals.push_back(new VariableDeclaration(this->parserPtr, motherNode));
	
}

ParseTreeNode* Parameter::getNodePtr()
{
	return this;

}

void Parameter::populateSearchResultsList(ParseTreeNode* motherNode)
{


	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}
