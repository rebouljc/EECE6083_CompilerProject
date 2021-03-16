#include "ProcedureBody.h"
#include "Declaration.h"
#include "Statement.h"
#include "TerminalNode.h"

ProcedureBody::ProcedureBody(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr)
{
	//Note: 3-13-2021: Added additional statement to set this node's parent node ptr, to enable reverse walking back up a tree.
	this->parentNodePtr = parentNodePtr;
	this->setParserPtr(parser);
	this->programNode_motherNode = motherNode;
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

	if (!this->linkedMemberNonterminals.empty() &&
		dynamic_cast<Declaration*>(this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1)) && 
		currentToken->getTokenValue() == ";"
	   )
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
	}

	else if (currentToken->getTokenValue() == "begin")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
		//If we see begin, we should stop parsing Declarations, return now, and start parsing statements.  If we do not, we will 
		//get improper parsing and eventually, the application will blow the stack somewhere.
		//Have to read the next token, so we don't mess up the statement method.
		currentToken = this->parserPtr->readNextToken();
		return;
		
	}
	else
	{
		this->linkedMemberNonterminals.push_back(new Declaration(this->parserPtr, motherNode, this));
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

	bool nested = false;
	/*for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		TerminalNode* testNode = dynamic_cast<TerminalNode*>(this->linkedMemberNonterminals.at(i));
		if (testNode != nullptr &&
			testNode->getNodeTokenValue() == "begin"
			)
		{
			//If the statement is nested 
			nested = true;
			break;
		}
	}*/
	if (!this->linkedMemberNonterminals.empty() &&
		dynamic_cast<Statement*>(this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1)) && 
		currentToken->getTokenValue() == ";")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
	}

	else if (currentToken->getTokenValue() == "end")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));

	}

	else if (currentToken->getTokenValue() == "procedure")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
		this->setIsValid(true);
		printf("-------->END PROCEDURE<--------------");
		
		return;
	}

	else
	{
		this->linkedMemberNonterminals.push_back(new Statement(this->parserPtr, motherNode, this));
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
	for (unsigned int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}
