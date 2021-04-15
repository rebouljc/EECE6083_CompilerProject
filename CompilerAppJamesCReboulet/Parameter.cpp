#include "Parameter.h"
#include "VariableDeclaration.h"

Parameter::Parameter(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr)
{
	//Note: 3-13-2021: Added additional statement to set this node's parent node ptr, to enable reverse walking back up a tree.
	this->parentNodePtr = parentNodePtr;
	this->setParserPtr(parser); 
	this->programNode_motherNode = motherNode;
	this->verifySyntaxCreateParseTree(0, motherNode);
	
}

void Parameter::generateIntermediateCodeFromParseTree(ofstream* outputFileStream)
{
	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->generateIntermediateCodeFromParseTree(outputFileStream);
	}
}

void Parameter::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{  
	//dynamic_cast takes more work.  Do static_cast.
	this->linkedMemberNonterminals.push_back(new VariableDeclaration(this->parserPtr, motherNode, this));
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


	for (unsigned int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}

