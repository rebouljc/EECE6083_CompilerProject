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
	Token* currentToken = this->parserPtr->readNextToken();
	bool varDeclFlag = false;
	bool procDeclFlag = false;
	bool typeDeclFlag = false;
	if (currentToken->getTokenValue() == "global")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
		this->verifySyntaxCreateParseTree(tokenCounter, motherNode);
	}

	else
	{   //Backup the tokenPtr index, so that the same token can be read correctly by the child methods.
		//Then, we don't have to worry about passing pointers to the current token through all of these constructors.
		//That gets confusing, and leads to many bugs that are difficult to find and fix.
		this->parserPtr->backupIndexToRead();

		this->linkedMemberNonterminals.push_back(new ProcedureDeclaration(this->parserPtr, motherNode));
		//Get rid of the node if there is nothing there, so it doesn't have to be included in the parse tree.
		ProcedureDeclaration* proc = dynamic_cast<ProcedureDeclaration*>(this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1));
		if (proc->getIsValid())
		{
			this->linkedMemberNonterminals.pop_back();
			procDeclFlag = true;
			
		}
		this->linkedMemberNonterminals.push_back(new VariableDeclaration(this->parserPtr, motherNode));
		VariableDeclaration* var = dynamic_cast<VariableDeclaration*>(this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1));
		if (var->getIsValid())
		{
			this->linkedMemberNonterminals.pop_back();
			varDeclFlag = true;
			
		}
		this->linkedMemberNonterminals.push_back(new TypeDeclaration(this->parserPtr, motherNode));
		TypeDeclaration* type = dynamic_cast<TypeDeclaration*>(this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1));
		if (type->getIsValid())
		{
			this->linkedMemberNonterminals.pop_back();
			typeDeclFlag = true;
			
		}
		
	}

	if (procDeclFlag || varDeclFlag || typeDeclFlag)
	{
		this->setIsValid(true);
		return;
	}

	//Else, we will return with a value of false and the Program Body class will pop the declaration off of the stack.
	//We will do the same thing here for statements, since there is the option of having a program with neither declarations or statements.
	this->parserPtr->backupIndexToRead(); //We need to backup the index, so that it is available to future methods.
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