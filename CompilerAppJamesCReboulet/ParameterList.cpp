#include "ParameterList.h"
#include "Parameter.h"
#include "TerminalNode.h"

ParameterList::ParameterList(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr)
{
	//Note: 3-13-2021: Added additional statement to set this node's parent node ptr, to enable reverse walking back up a tree.
	this->parentNodePtr = parentNodePtr;
	this->setParserPtr(parser);
	this->programNode_motherNode = motherNode;
	this->verifySyntaxCreateParseTree(0, motherNode);
	
}

void ParameterList::generateIntermediateCodeFromParseTree(ifstream* outputFileStream)
{
	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->generateIntermediateCodeFromParseTree(outputFileStream);
	}
}

void ParameterList::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{   
	Token* currentToken = parserPtr->getCurrentlyReadToken();
	this->linkedMemberNonterminals.push_back(new Parameter(this->parserPtr, motherNode, this));
	ParseTreeNode* lastNode = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);
	if (!lastNode->getIsValid())
	{
		this->linkedMemberNonterminals.pop_back();
		return;  //We definitely do not have a parameterList if there is no <parameter>
	}
	
	
	else if (currentToken->getTokenValue() == ",")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
	}

	else
	{
		//There is no comma, so we return.  Do not set index back to previous.  Be careful with doing this in <Name> and <Destination> too.
		this->setIsValid(true); //We know that if we have gotten here, we at least have a valid <parameter> or else we would have returned then.
		return;
	}
	this->linkedMemberNonterminals.push_back(new ParameterList(this->parserPtr, motherNode, this));
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


	for (unsigned int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}
