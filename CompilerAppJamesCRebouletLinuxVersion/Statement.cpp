#include "Statement.h"
#include "AssignmentStatement.h"
#include "IfStatement.h"
#include "LoopStatement.h"
#include "ReturnStatement.h"

Statement::Statement(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr)
{
	//Note: 3-13-2021: Added additional statement to set this node's parent node ptr, to enable reverse walking back up a tree.
	this->parentNodePtr = parentNodePtr;
	this->setParserPtr(parser);
	this->programNode_motherNode = motherNode;
	this->verifySyntaxCreateParseTree(0, motherNode);
	
}

void Statement::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{   //Completed 2-23-2021

	Token* currentToken = this->parserPtr->getCurrentlyReadToken();
	bool assnStmtFlag = false;
	bool ifStmtFlag = false;
	bool loopStmtFlag = false;
	bool returnStmtFlag = false;
	//printf("\nStatement_CurrentToken = %s", currentToken->getTokenValue().c_str());
	

	this->linkedMemberNonterminals.push_back(new AssignmentStatement(this->parserPtr, motherNode, this));
	//Get rid of the node if there is nothing there, so it doesn't have to be included in the parse tree.
	ParseTreeNode* stmt = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);
	if (!stmt->getIsValid())
	{
		this->linkedMemberNonterminals.pop_back();
	}
	else
	{
		assnStmtFlag = true;
		this->setIsValid(true);
		//Try giving back the value. 
		//this->parserPtr->resetTokenReadIndexToPrevious();
		return;
	}
	this->linkedMemberNonterminals.push_back(new IfStatement(this->parserPtr, motherNode, this));
	stmt = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);
	if (!stmt->getIsValid())
	{
		this->linkedMemberNonterminals.pop_back();
	}
	else
	{
		ifStmtFlag = true;
		this->setIsValid(true);
		return;
	}
	this->linkedMemberNonterminals.push_back(new LoopStatement(this->parserPtr, motherNode, this));
	stmt = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);
	if (!stmt->getIsValid())
	{
		this->linkedMemberNonterminals.pop_back();
	}
	else
	{
		loopStmtFlag = true;
		this->setIsValid(true);
		return;
	}

	this->linkedMemberNonterminals.push_back(new ReturnStatement(this->parserPtr, motherNode, this));
	stmt = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);
	if (!stmt->getIsValid())
	{
		this->linkedMemberNonterminals.pop_back();
	}
	else
	{
		returnStmtFlag = true;
		this->setIsValid(true);
		//Try giving back the value. 
		//this->parserPtr->resetTokenReadIndexToPrevious();
		return;
	}

	//if (assnStmtFlag || ifStmtFlag || loopStmtFlag || returnStmtFlag)
	//{
	//	this->setIsValid(true);
	//}

	//Else, we will return with a value of false and the Program Body class will pop the declaration off of the stack.
	//We will do the same thing here for statements, since there is the option of having a program with neither declarations or statements.

	//return;

}

ParseTreeNode* Statement::getNodePtr()
{
	return this;

}

void Statement::populateSearchResultsList(ParseTreeNode* motherNode)
{


	for (unsigned int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}
