#include "Bound.h"
#include "TerminalNode.h"
#include "Number.h"

Bound::Bound(Token* token, Parser* parser, ParseTreeNode* motherNode)
{
	this->token = token;
	this->setParserPtr(parser);
	this->verifySyntaxCreateParseTree(0, motherNode);
}

void Bound::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{
	
	if (this->token->getTokenValue() == "NUMBER")
	{
		this->linkedMemberNonterminals.push_back(new Number(this->token));
	}

	else
	{
		//Throw an exception or generate an error.  This is a problem.
	}

}

ParseTreeNode* Bound::getNodePtr()
{
	return this;

}

void Bound::populateSearchResultsList(ParseTreeNode* motherNode)
{


	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}

void Bound::populateLocalSearchResultsList()
{
	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList();
	}

}
