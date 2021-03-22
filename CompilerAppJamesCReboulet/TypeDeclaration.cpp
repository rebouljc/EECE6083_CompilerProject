#include "TypeDeclaration.h"
#include "Token.h"
#include "TypeMark.h"
#include "Identifier.h"
#include "Bound.h"

TypeDeclaration::TypeDeclaration(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr)
{
	//Note: 3-13-2021: Added additional statement to set this node's parent node ptr, to enable reverse walking back up a tree.
	this->parentNodePtr = parentNodePtr;
	this->setParserPtr(parser);
	this->programNode_motherNode = motherNode;
	this->verifySyntaxCreateParseTree(0, motherNode);
	
	
}

void TypeDeclaration::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{  
	//Same as ProcedureDeclaration::verifySyntaxCreateParseTree() method, except "variable" is used, and <bound> is substituted for 
	//<parameter_list>.

	  //Needs to be modified for program body.  Make it recursive to handle multiple declarations and statements.
	//Read the next token here.
	Token* currentToken = parserPtr->getCurrentlyReadToken();
	//printf("\nTypeDeclaration_CurrentToken = %s", currentToken->getTokenValue().c_str());
	if (tokenCounter == 0)
	{
		if (currentToken->getTokenValue() == "type")
		{
			this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
		}

		else
		{
			this->setIsValid(false);
			return;
		}

	}
	else if (tokenCounter == 1)
	{
		if (currentToken->getTokenType() == "IDENTIFIER")
		{
			this->linkedMemberNonterminals.push_back(new Identifier(currentToken, motherNode, "LOCAL", this));
		}

		else
		{
			//Throw an exception and return.
			return;
		}

	}
	else if (tokenCounter == 2)
	{
		if (currentToken->getTokenValue() == "is")
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
		this->setIsValid(true);
		return;
	}

	else
	{
		return; //We return with setIsValid(false) by default.
	}



	++tokenCounter;
	//Read in the next token now, if we get here, before recursion.
	currentToken = parserPtr->readNextToken();
	this->verifySyntaxCreateParseTree(tokenCounter, motherNode);
	return;



}

ParseTreeNode* TypeDeclaration::getNodePtr()
{
	return this;

}

void TypeDeclaration::populateSearchResultsList(ParseTreeNode* motherNode)
{


	for (unsigned int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}

