#include "TypeMark.h"
#include "TerminalNode.h"
#include "Identifier.h"

TypeMark::TypeMark(Parser* parser, ParseTreeNode* motherNode)
{
	this->setParserPtr(parser);
	this->verifySyntaxCreateParseTree(0, motherNode);
}

void TypeMark::createEnumList(ParseTreeNode* motherNode)
{
	Token* currentToken = this->parserPtr->getCurrentlyReadToken();
	//Create the new identifier and check its validity.
	if (currentToken->getTokenValue() == "{")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
	}

	if (currentToken->getTokenType() == "IDENTIFIER")
	{
		this->linkedMemberNonterminals.push_back(new Identifier(currentToken, motherNode, "GLOBAL"));
	}

	else if (currentToken->getTokenValue() == ",")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
	}

	else if (currentToken->getTokenValue() == "}")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
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

		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
		
	}

	else if (currentToken->getTokenValue() == "enum")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
		this->createEnumList(motherNode);
		this->setIsValid(true);
		

	}

	else if (currentToken->getTokenType() == "IDENTIFIER")
	{
		this->linkedMemberNonterminals.push_back(new Identifier(currentToken, motherNode, "GLOBAL"));
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


	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}

void TypeMark::populateLocalSearchResultsList()
{
	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList();
	}

}