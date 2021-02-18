#include "Parameter.h"


Parameter::Parameter(Parser* parser, ParseTreeNode* motherNode)
{
	static_cast<ParseTreeNode*>(this)->setParserPtr(parser); //We have to do this crazy crap, because this class has multiple inheritance.
	this->verifySyntaxCreateParseTree(0, motherNode);
}

void Parameter::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{  
	dynamic_cast<VariableDeclaration*>(this)->verifySyntaxCreateParseTree(tokenCounter, motherNode);
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
