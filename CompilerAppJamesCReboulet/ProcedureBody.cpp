#include "ProcedureBody.h"
#include "Declaration.h"
#include "Statement.h"
#include "TerminalNode.h"

ProcedureBody::ProcedureBody(Parser* parser, ParseTreeNode* motherNode)
{
	this->setParserPtr(parser);
	this->verifySyntaxCreateParseTree(0, motherNode);
}

void ProcedureBody::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{
	//Both of these methods are recursive methods.  But, there can only be one "Program Body" so we have to divide the 
		//statements and the declarations up into separate methods.
	this->verifySyntaxCreateParseTreeDeclarationParser(motherNode);
	this->verifySyntaxCreateParseTreeStatementParser(motherNode);
}

void ProcedureBody::verifySyntaxCreateParseTreeDeclarationParser(ParseTreeNode* motherNode)
{   //Same as program body with a few changes to the reserved words.

	Token* currentToken = this->parserPtr->getCurrentlyReadToken();
	printf("\nProcedureBody_CurrentToken = %s", currentToken->getTokenValue().c_str());

	if (currentToken->getTokenValue() == ";")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
	}

	else if (currentToken->getTokenValue() == "begin")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
		//If we see begin, we should stop parsing Declarations, return now, and start parsing statements.  If we do not, we will 
		//get improper parsing and eventually, the application will blow the stack somewhere.
		//Have to read the next token, so we don't mess up the statement method.
		currentToken = this->parserPtr->readNextToken();
		return;
		
	}
	else
	{
		this->linkedMemberNonterminals.push_back(new Declaration(this->parserPtr, motherNode));
		ParseTreeNode* decl = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);
		if (!decl->getIsValid())
		{
			this->linkedMemberNonterminals.pop_back();
			
		}
	}

	currentToken = this->parserPtr->readNextToken();
	this->verifySyntaxCreateParseTreeDeclarationParser(motherNode);
}
void ProcedureBody::verifySyntaxCreateParseTreeStatementParser(ParseTreeNode* motherNode)
{
	Token* currentToken = this->parserPtr->getCurrentlyReadToken();
	printf("\nProcedureBody_CurrentToken = %s", currentToken->getTokenValue().c_str());

	if (currentToken->getTokenValue() == ";")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
	}

	else if (currentToken->getTokenValue() == "end")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));

	}

	else if (currentToken->getTokenValue() == "procedure")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
		this->setIsValid(true);
		printf("-------->END PROCEDURE<--------------");
		//currentToken = this->parserPtr->readNextToken(); //Hopefully, if we read here, this will fix the infinite recursion back into <Factor>
		return;
	}

	else
	{
		this->linkedMemberNonterminals.push_back(new Statement(this->parserPtr, motherNode));
		ParseTreeNode* testNode = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);
		if (!testNode->getIsValid())
		{
			this->linkedMemberNonterminals.pop_back();
			
		}
	}
	currentToken = this->parserPtr->readNextToken();
	this->verifySyntaxCreateParseTreeStatementParser(motherNode);
}

ParseTreeNode* ProcedureBody::getNodePtr()
{
	return this;
}

void ProcedureBody::populateSearchResultsList(ParseTreeNode* motherNode)
{
	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}