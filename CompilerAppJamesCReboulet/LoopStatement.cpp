#include "LoopStatement.h"

LoopStatement::LoopStatement(Parser* parser, ParseTreeNode* motherNode)
{
	this->setParserPtr(parser);
	this->verifySyntaxCreateParseTree(0, motherNode);
}

void LoopStatement::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{   //Needs to be modified for program body.  Make it recursive to handle multiple declarations and statements.


}

ParseTreeNode* LoopStatement::getNodePtr()
{
	return this;

}

void LoopStatement::populateSearchResultsList(ParseTreeNode* motherNode)
{


	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}