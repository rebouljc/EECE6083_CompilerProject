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
	//If we do not check for this, we will get a problem of infinite recursion.
	
	this->linkedMemberNonterminals.push_back(new ProcedureHeader(this->parserPtr, motherNode));

	ParseTreeNode* procHead = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);
	if (!procHead->getIsValid())
	{
		this->linkedMemberNonterminals.pop_back();
		return;  //If we don't have a procedure header, there is no reason to check for a procedure body, or else we continue to recurse back to declaration.  

	}

	this->verifySyntaxCreateParseTree(tokenCounter, motherNode);

	this->linkedMemberNonterminals.push_back(new ProcedureBody(this->parserPtr, motherNode));

	ParseTreeNode* procBody = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);
	if (!procBody->getIsValid())
	{
		this->linkedMemberNonterminals.pop_back();
		return; //We return with bool isValid = false; by default;

	}

	//If we get here, we have definitely created a valid <ProcedureDeclaration>, so we set its isValid = true;
	this->setIsValid(true);
	return;




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