#include "Declaration.h"
#include "TerminalNode.h"
#include "ProcedureDeclaration.h"
#include "VariableDeclaration.h"
#include "TypeDeclaration.h"

/*NOTE:  REMEMBER TO CALL this->parserPtr->backupIndexToRead() if a recursive function pops a newly created object from the vector.
  Otherwise, that particular token will have already been read and it will be ignored in future methods/classes that need it.*/

Declaration::Declaration(Parser* parser, ParseTreeNode* motherNode)
{
	this->setParserPtr(parser);
	this->verifySyntaxCreateParseTree(0, motherNode);
}


void Declaration::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{   //Needs to be modified for program body.  Make it recursive to handle multiple declarations and statements.
	Token* currentToken = this->parserPtr->getCurrentlyReadToken();
	printf("\nDeclaration_CurrentToken = %s", currentToken->getTokenValue().c_str());
	
	bool varDeclFlag = false;
	bool procDeclFlag = false;
	bool typeDeclFlag = false;
	if (currentToken->getTokenValue() == "global")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
		currentToken = this->parserPtr->readNextToken();  //This will store the currently read token in parserPtr, even though it returns a useless Token* here.
		++tokenCounter; //Increment the token counter, so that if the word "global" is present, there should be at least 1 declaration.
		this->verifySyntaxCreateParseTree(tokenCounter, motherNode);
	}

	else
	{   
		
		this->linkedMemberNonterminals.push_back(new ProcedureDeclaration(this->parserPtr, motherNode));
		//Get rid of the node if there is nothing there, so it doesn't have to be included in the parse tree.
		ParseTreeNode* decl = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);
		if (!decl->getIsValid())
		{
			this->linkedMemberNonterminals.pop_back();
			
			
		}
		else
		{
			this->setIsValid(true);
			return; //If one is true, there is no reason to test any more of them.  The call stack gets way too big.

		}
		this->linkedMemberNonterminals.push_back(new VariableDeclaration(this->parserPtr, motherNode));
		decl = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);
		if (!decl->getIsValid())
		{
			this->linkedMemberNonterminals.pop_back();
			
			
		}
		else
		{
			this->setIsValid(true);
			return;
		}
		this->linkedMemberNonterminals.push_back(new TypeDeclaration(this->parserPtr, motherNode));
		decl = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);
		if (!decl->getIsValid())
		{
			this->linkedMemberNonterminals.pop_back();
			
			
		}
		else
		{
			this->setIsValid(true);
			return;
		}
		
	}

	//Else, we will return with a value of false and the Program Body class will pop the declaration off of the stack.
	//We will do the same thing here for statements, since there is the option of having a program with neither declarations or statements.
	
	return;

}

ParseTreeNode* Declaration::getNodePtr()
{
	return this;

}

void Declaration::populateSearchResultsList(ParseTreeNode* motherNode)
{


	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}

void Declaration::populateLocalSearchResultsList()
{
	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList((ParseTreeNode*)this);
	}

}