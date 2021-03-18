#include "ProcedureHeader.h"
#include "Identifier.h"
#include "TypeMark.h"
#include "ParameterList.h"

ProcedureHeader::ProcedureHeader(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr)
{
	//Note: 3-13-2021: Added additional statement to set this node's parent node ptr, to enable reverse walking back up a tree.
	this->parentNodePtr = parentNodePtr;
	this->setParserPtr(parser);
	this->programNode_motherNode = motherNode;
	this->verifySyntaxCreateParseTree(0, motherNode);
	
}

void ProcedureHeader::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{   //Needs to be modified for program body.  Make it recursive to handle multiple declarations and statements.
	//Read the next token here.
	Token* currentToken = parserPtr->getCurrentlyReadToken();
	printf("\nProcedureHeader_CurrentToken = %s", currentToken->getTokenValue().c_str());
	if (tokenCounter == 0)
	{
		if (currentToken->getTokenValue() == "procedure")
		{
			this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
		}

		else
		{
			return;
		}

	}
	else if (tokenCounter == 1)
	{
		if (currentToken->getTokenType() == "IDENTIFIER")
		{
			
			this->linkedMemberNonterminals.push_back(new Identifier(currentToken, motherNode, "LOCAL", this, true));
			
		}

		else
		{
			//Throw an exception and return.
			return;
		}

	}
	else if (tokenCounter == 2)
	{
		if (currentToken->getTokenValue() == ":")
		{
			this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
		}

		else
		{
			//Throw an exception and return.
			return;
		}

	}

	else if (tokenCounter == 3) //If it is equal to 3 and we have made it this far, we need a type mark.
	{
		this->linkedMemberNonterminals.push_back(new TypeMark(this->parserPtr, motherNode, this));
	}

	else if (tokenCounter == 4)
	{
		if (currentToken->getTokenValue() == "(")
		{
			this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
		}

		else
		{
			//Throw an exception.
			return;
		}
	}

	else if (tokenCounter == 5)
	{
		this->linkedMemberNonterminals.push_back(new ParameterList(this->parserPtr, motherNode, this));
		//If there are no parameters, then pop_back() the vector.
		ParseTreeNode* param = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);
		if (!param->getIsValid())
		{
			this->linkedMemberNonterminals.pop_back();
		}
	}

	else if (tokenCounter == 6)
	{
		if (currentToken->getTokenValue() == ")")
		{
			this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
			//Read the next token, for now.  Since this is causing issues.
			currentToken = this->parserPtr->readNextToken();
		}

		else
		{
			//Throw an exception and return;
			
		}

		//Right here, we return now, if this recursive method is complete.
		this->setIsValid(true);
		return;
	}

	++tokenCounter;
	//Read in the next token now, if we get here, before recursion.
	currentToken = parserPtr->readNextToken();
	this->verifySyntaxCreateParseTree(tokenCounter, motherNode);
	return;

}

ParseTreeNode* ProcedureHeader::getNodePtr()
{
	return this;

}

void ProcedureHeader::populateSearchResultsList(ParseTreeNode* motherNode)
{


	for (unsigned int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}

unsigned int ProcedureHeader::getLinkedMemberNonterminalsSize()
{
	return this->linkedMemberNonterminals.size();
}
