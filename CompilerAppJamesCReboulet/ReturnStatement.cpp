#include "ReturnStatement.h"

ReturnStatement::ReturnStatement(Parser* parser, ParseTreeNode* motherNode)
{
	this->setParserPtr(parser);
	this->verifySyntaxCreateParseTree(0, motherNode);
}

void ReturnStatement::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{   //Needs to be modified for program body.  Make it recursive to handle multiple declarations and statements.


}

ParseTreeNode* ReturnStatement::getNodePtr()
{
	return this;

}

void ReturnStatement::populateSearchResultsList(ParseTreeNode* motherNode)
{


	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}