#include "TypeMark.h"
#include "TerminalNode.h"
#include "Identifier.h"
#include "Program.h"
#include "VariableDeclaration.h"
#include "ProcedureHeader.h"



TypeMark::TypeMark(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr)
{
	//Note: 3-13-2021: Added additional statement to set this node's parent node ptr, to enable reverse walking back up a tree.
	this->parentNodePtr = parentNodePtr;
	this->setParserPtr(parser);
	this->programNode_motherNode = motherNode;
	this->verifySyntaxCreateParseTree(0, motherNode);
	
}


void TypeMark::generateIntermediateCodeFromParseTree(ofstream* outputFileStream, vector<ParseTreeNode*>* declSymbolTablePtr)
{
	
	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->generateIntermediateCodeFromParseTree(outputFileStream, declSymbolTablePtr);
	}
}


void TypeMark::createEnumList(ParseTreeNode* motherNode)
{
	Token* currentToken = this->parserPtr->getCurrentlyReadToken();
	//Create the new identifier and check its validity.
	if (currentToken->getTokenValue() == "{")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this, this->programNode_motherNode));
	}

	if (currentToken->getTokenType() == "IDENTIFIER")
	{
		this->linkedMemberNonterminals.push_back(new Identifier(currentToken, motherNode, "LOCAL", this));
	}

	else if (currentToken->getTokenValue() == ",")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this, this->programNode_motherNode));
	}

	else if (currentToken->getTokenValue() == "}")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this, this->programNode_motherNode));
		return;
	}
	else
	{
		return;  //Here, again, we will have to throw some type of syntax error, depending on what is missing.
		         //We need to prevent infinite recursion here.
	}
	currentToken = this->parserPtr->readNextToken();
	this->createEnumList(motherNode);
}

void TypeMark::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{   //This is not to be a recursive function.  It can't be, since it is an | situation.
	Token* currentToken = this->parserPtr->getCurrentlyReadToken();
	Identifier* ident = nullptr;
	VariableDeclaration* varDecl = nullptr;
	ProcedureHeader* procHead = nullptr;
	if (currentToken->getTokenValue() == "integer" ||
		currentToken->getTokenValue() == "float"   ||
		currentToken->getTokenValue() == "string"  ||
		currentToken->getTokenValue() == "bool"
	   )
	{

		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this, this->programNode_motherNode));
		if ((varDecl = dynamic_cast<VariableDeclaration*>(this->parentNodePtr)) != nullptr)
		{
			for (int i = 0; i < varDecl->getLinkedMemberNonterminalsList().size(); ++i)
			{
				if ((ident = dynamic_cast<Identifier*>(varDecl->getLinkedMemberNonterminalsList().at(i))) != nullptr)
				{
					ident->setTypeMarkString(currentToken->getTokenValue());
					break;
				}
			}
		}

		else if ((procHead = dynamic_cast<ProcedureHeader*>(this->parentNodePtr)) != nullptr)
		{
			for (int i = 0; i < procHead->getLinkedMemberNonterminalsList().size(); ++i)
			{
				if ((ident = dynamic_cast<Identifier*>(procHead->getLinkedMemberNonterminalsList().at(i))) != nullptr)
				{
					ident->setTypeMarkString(currentToken->getTokenValue());
					break;
				}
			}
		}
		
	}

	else if (currentToken->getTokenValue() == "enum")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this, this->programNode_motherNode));
		this->createEnumList(motherNode);
		this->setIsValid(true);
		

	}
	
	else
	{
		//Here, we would probably throw some type of exception, since every procedure requires a <type_mark>.
	}

	return;
}

ParseTreeNode* TypeMark::getNodePtr()
{
	return this;

}

void TypeMark::populateSearchResultsList(ParseTreeNode* motherNode)
{


	for (unsigned int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}

