#include "ProcedureCall.h"
#include "TerminalNode.h"
#include "Identifier.h"
#include "ArgumentList.h"
#include "IdentifierNotDeclaredException.h"

//2-23-2021: Code needs to be modified.  This is type mark code.

ProcedureCall::ProcedureCall(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr)
{
	//Note: 3-13-2021: Added additional statement to set this node's parent node ptr, to enable reverse walking back up a tree.
	this->parentNodePtr = parentNodePtr;
	this->setParserPtr(parser);
	this->programNode_motherNode = motherNode;
	this->verifySyntaxCreateParseTree(0, motherNode);
	//Semantic Check
	try
	{
		if (this->getIsValid())
		{
			bool checkScopeResult = this->checkIdentifierFollowsScopingRules();
		}
	}
	catch (IdentifierNotDeclaredException& e)
	{
		if (!this->parserPtr->searchPredefinedRuntimeProceduresList(dynamic_cast<Identifier*>(this->linkedMemberNonterminals.at(0))->getNodeTokenValue()))
		{
			cout << endl << endl << e.what() << dynamic_cast<Identifier*>(this->linkedMemberNonterminals.at(0))->getNodeTokenLineNumber()
				<< " Identifier Name: " << dynamic_cast<Identifier*>(this->linkedMemberNonterminals.at(0))->getNodeTokenValue() << endl;


			this->parserPtr->setCompilerErrorsPresentFlag(true);
		}
		
	}

	
}

void ProcedureCall::generateIntermediateCodeFromParseTree(ofstream* outputFileStream, vector<ParseTreeNode*>* declSymbolTablePtr)
{
	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->generateIntermediateCodeFromParseTree(outputFileStream, declSymbolTablePtr);
	}
}

ProcedureCall::ProcedureCall(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr, Token* stolenToken)
{
	//Note: 3-13-2021: Added additional statement to set this node's parent node ptr, to enable reverse walking back up a tree.
	this->parentNodePtr = parentNodePtr;
	this->setParserPtr(parser);
	this->setStolenToken(stolenToken);
	this->verifySyntaxCreateParseTree(0, motherNode);
	//Semantic Check
	try
	{
		if (this->getIsValid())
		{
			bool checkScopeResult = this->checkIdentifierFollowsScopingRules();
		}
	}
	catch (IdentifierNotDeclaredException& e)
	{
		if (!this->parserPtr->searchPredefinedRuntimeProceduresList(dynamic_cast<Identifier*>(this->linkedMemberNonterminals.at(0))->getNodeTokenValue()))
		{
			cout << endl << endl << e.what() << dynamic_cast<Identifier*>(this->linkedMemberNonterminals.at(0))->getNodeTokenLineNumber()
				<< " Identifier Name: " << dynamic_cast<Identifier*>(this->linkedMemberNonterminals.at(0))->getNodeTokenValue() << endl;

			this->parserPtr->setCompilerErrorsPresentFlag(true);
		}
		
		
	}

}

void ProcedureCall::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{   
	//This is exactly the same as <destination> class, so we will simply copy the method.  These changes are as of 2/28/2021.
	//Originally destination was defined on 2/26/2021.

	Token* currentToken = parserPtr->getCurrentlyReadToken();
	if (tokenCounter == 0 && this->stolenToken != nullptr)
	{
		currentToken = this->stolenToken;
	}
	
	//printf("\nProcedureCall_CurrentToken = %s", currentToken->getTokenValue().c_str());
	if (currentToken->getTokenType() == "IDENTIFIER")
	{
		this->linkedMemberNonterminals.push_back(new Identifier(currentToken, motherNode, "LOCAL", this));
		//recurse

	}

	else if (currentToken->getTokenValue() == "(")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this, this->programNode_motherNode));
		//recurse
	}

	else if (currentToken->getTokenValue() == ")")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this, this->programNode_motherNode));
		this->setIsValid(true);
		return;
	}

	else if (tokenCounter == 2)
	{
		//The option of having an ArgumentList here is optional, so if we don't have an expression, we need to get rid of the pointer
		//to the class within the parse tree, since it makes things more confusing.  First we have to add it to the tree and then check.

		this->linkedMemberNonterminals.push_back(new ArgumentList(this->parserPtr, motherNode, this));
		bool isValid = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1)->getIsValid();
		if (!isValid)
		{
			this->linkedMemberNonterminals.pop_back();
		}

		this->parserPtr->resetTokenReadIndexToPrevious();  //Try this to see what happens.

		//recurse

	}

	//Otherwise, we return.  We forgot to return here.
	else
	{
		return;
	}
	++tokenCounter;
	currentToken = this->parserPtr->readNextToken();
	this->verifySyntaxCreateParseTree(tokenCounter, motherNode);
	return;
}

ParseTreeNode* ProcedureCall::getNodePtr()
{
	return this;

}

void ProcedureCall::populateSearchResultsList(ParseTreeNode* motherNode)
{


	for (unsigned int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}

bool ProcedureCall::checkIdentifierFollowsScopingRules()
{
	ParseTreeNode* identifierToCheck = nullptr;
	bool identPresent = this->searchSymbolTable(this->linkedMemberNonterminals.at(0), identifierToCheck);
	if (identPresent)
	{
		//printf("\nIdentFound %s", dynamic_cast<Identifier*>(this->linkedMemberNonterminals.at(0))->getNodeTokenValue().c_str());

	}

	else
	{
		//We throw an exception.  Identifier is being assigned, but has not been declared locally or globally.
		throw IdentifierNotDeclaredException();
	}

	return identPresent;
}
