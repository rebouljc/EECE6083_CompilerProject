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
	bool isValid = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1)->getIsValid();
	if (!isValid)
	{
		this->linkedMemberNonterminals.pop_back();
		return; //This will not be a valid parameter then.
	}

	this->setIsValid(true);
	return;
	
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

void Parameter::populateLocalSearchResultsList()
{
	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList((ParseTreeNode*)this);
	}

}
