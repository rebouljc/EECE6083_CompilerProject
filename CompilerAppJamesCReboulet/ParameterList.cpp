#include "ParameterList.h"
#include "Parameter.h"
#include "TerminalNode.h"

ParameterList::ParameterList(Parser* parser, ParseTreeNode* motherNode)
{
	this->setParserPtr(parser);
	this->verifySyntaxCreateParseTree(0, motherNode);
}

void ParameterList::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{   
	Token* currentToken = parserPtr->getCurrentlyReadToken();
	this->linkedMemberNonterminals.push_back(new Parameter(this->parserPtr, motherNode));
	ParseTreeNode* lastNode = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);
	if (!lastNode->getIsValid())
	{
		this->linkedMemberNonterminals.pop_back();
		return;  //We definitely do not have a parameterList if there is no <parameter>
	}
	
	
	else if (currentToken->getTokenValue() == ",")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
	}

	else
	{
		//There is no comma, so we return.  Do not set index back to previous.  Be careful with doing this in <Name> and <Destination> too.
		return;
	}
	this->linkedMemberNonterminals.push_back(new ParameterList(this->parserPtr, motherNode));
	lastNode = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);
	if (!lastNode->getIsValid())
	{
		this->linkedMemberNonterminals.pop_back(); 
	}

		return;
	
	currentToken = parserPtr->readNextToken();
	++tokenCounter;
	this->verifySyntaxCreateParseTree(tokenCounter, motherNode);
}

ParseTreeNode* ParameterList::getNodePtr()
{
	return this;

}

void ParameterList::populateSearchResultsList(ParseTreeNode* motherNode)
{


	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}
