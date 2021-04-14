#include "TypeMark.h"
#include "TerminalNode.h"
#include "Identifier.h"

TypeMark::TypeMark(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr)
{
	//Note: 3-13-2021: Added additional statement to set this node's parent node ptr, to enable reverse walking back up a tree.
	this->parentNodePtr = parentNodePtr;
	this->setParserPtr(parser);
	this->programNode_motherNode = motherNode;
	this->verifySyntaxCreateParseTree(0, motherNode);
	
}


void TypeMark::generateIntermediateCodeFromParseTree(ifstream* outputFileStream)
{
	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->generateIntermediateCodeFromParseTree(outputFileStream);
	}
}


void TypeMark::createEnumList(ParseTreeNode* motherNode)
{
	Token* currentToken = this->parserPtr->getCurrentlyReadToken();
	//Create the new identifier and check its validity.
	if (currentToken->getTokenValue() == "{")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
	}

	if (currentToken->getTokenType() == "IDENTIFIER")
	{
		this->linkedMemberNonterminals.push_back(new Identifier(currentToken, motherNode, "LOCAL", this));
	}

	else if (currentToken->getTokenValue() == ",")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
	}

	else if (currentToken->getTokenValue() == "}")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
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
	if (currentToken->getTokenValue() == "integer" ||
		currentToken->getTokenValue() == "float"   ||
		currentToken->getTokenValue() == "string"  ||
		currentToken->getTokenValue() == "bool"
	   )
	{

		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
		
	}

	else if (currentToken->getTokenValue() == "enum")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
		this->createEnumList(motherNode);
		this->setIsValid(true);
		

	}

	else if (currentToken->getTokenType() == "IDENTIFIER")
	{
		this->linkedMemberNonterminals.push_back(new Identifier(currentToken, motherNode, "LOCAL", this));
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

