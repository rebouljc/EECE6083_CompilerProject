#include "ArithOp_.h"
#include "TerminalNode.h"
#include "Identifier.h"

//2-23-2021: Code needs to be modified.  This is type mark code.
ArithOp_::ArithOp_(Parser* parser, ParseTreeNode* motherNode)
{
	this->setParserPtr(parser);
	this->verifySyntaxCreateParseTree(0, motherNode);
}

void ArithOp_::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{

}

ParseTreeNode* ArithOp_::getNodePtr()
{
	return this;

}

void ArithOp_::populateSearchResultsList(ParseTreeNode* motherNode)
{


	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}