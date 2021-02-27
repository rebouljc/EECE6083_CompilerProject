#include "Name.h"
#include "TerminalNode.h"
#include "Identifier.h"

//2-23-2021: Code needs to be modified.  This is type mark code.
Name::Name(Parser* parser, ParseTreeNode* motherNode)
{
	this->setParserPtr(parser);
	this->verifySyntaxCreateParseTree(0, motherNode);
}

void Name::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{

}

ParseTreeNode* Name::getNodePtr()
{
	return this;

}

void Name::populateSearchResultsList(ParseTreeNode* motherNode)
{


	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}