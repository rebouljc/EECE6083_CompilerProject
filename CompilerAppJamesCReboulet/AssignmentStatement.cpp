#include "AssignmentStatement.h"
#include "Destination.h"
#include "Identifier.h"
#include "Expression.h"

AssignmentStatement::AssignmentStatement(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr)
{
	//Note: 3-13-2021: Added additional statement to set this node's parent node ptr, to enable reverse walking back up a tree.
	this->parentNodePtr = parentNodePtr;
	this->setParserPtr(parser);
	this->programNode_motherNode = motherNode;
	this->verifySyntaxCreateParseTree(0, motherNode);
	
}

void AssignmentStatement::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{   //Needs to be modified for Statement
	Token* currentToken = this->parserPtr->getCurrentlyReadToken();


	this->linkedMemberNonterminals.push_back(new Destination(this->parserPtr, motherNode, this));
	ParseTreeNode* dest = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);

	if (!dest->getIsValid())
	{
		this->linkedMemberNonterminals.pop_back();
		return;  //We need to get out of here, since we know we do not have a valid <Destination>, since it doesn't begin with an identifier.
	}

	currentToken = this->parserPtr->readNextToken();
   
	
    //Read the next token, to prevent this from blowing up if we have a valid <Destination>
	

	if (currentToken->getTokenType() == "ASSIGNMENT")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
		
	}

	currentToken = this->parserPtr->readNextToken();
	TerminalNode* checkNode = nullptr;
	if ((checkNode = dynamic_cast<TerminalNode*>(this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1))) != nullptr)
	{
		if (checkNode->getNodeTokenType() == "ASSIGNMENT")
		{
			this->linkedMemberNonterminals.push_back(new Expression(this->parserPtr, motherNode, this));
			ParseTreeNode* expr = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);
			if (!expr->getIsValid())
			{
				this->linkedMemberNonterminals.pop_back();
				return;  //Set is valid will be false here.
			}

			this->setIsValid(true);
		}
	}
	
	
	return;
	
	
}

ParseTreeNode* AssignmentStatement::getNodePtr()
{
	return this;

}

void AssignmentStatement::populateSearchResultsList(ParseTreeNode* motherNode)
{


	for (unsigned int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}
