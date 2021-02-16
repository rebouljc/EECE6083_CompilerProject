#include "ProcedureDeclaration.h"
#include "ProcedureBody.h"
#include "ProcedureHeader.h"
#include "Token.h"


ProcedureDeclaration::ProcedureDeclaration(Parser* parser, ParseTreeNode* motherNode)
{
	this->setParserPtr(parser);
	this->verifySyntaxCreateParseTree(0, motherNode);
	
}

void ProcedureDeclaration::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{   //Needs to be modified for program body.  Make it recursive to handle multiple declarations and statements.
	//Do not read the next token, it has already been passed from its parent object
	bool procHeadFlag = false;
	bool procBodyFlag = false;
	//No reason to read the next token here.  It is not used and makes everything else confusing.  DON'T FRICKING DO IT!!

	this->linkedMemberNonterminals.push_back(new ProcedureHeader(this->parserPtr, motherNode));

	ProcedureHeader* procHead = dynamic_cast<ProcedureHeader*>(this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1));
	if (procHead->getIsValid())
	{
		this->linkedMemberNonterminals.pop_back();

	}
	this->linkedMemberNonterminals.push_back(new ProcedureBody(this->parserPtr, motherNode));

	ProcedureBody* procBody = dynamic_cast<ProcedureBody*>(this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1));
	if (procBody->getIsValid())
	{
		this->linkedMemberNonterminals.pop_back();

	}



}

ParseTreeNode* ProcedureDeclaration::getNodePtr()
{
	return this;

}

void ProcedureDeclaration::populateSearchResultsList(ParseTreeNode* motherNode)
{


	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}