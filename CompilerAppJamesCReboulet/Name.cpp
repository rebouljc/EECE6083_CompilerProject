#include "Name.h"
#include "TerminalNode.h"
#include "Identifier.h"
#include "Expression.h"
#include "IdentifierNotDeclaredException.h"
#include "Number.h"
#include "ArrayIndexNotAnIntegerLiteralException.h"

//2-23-2021: Code needs to be modified.  This is type mark code.
Name::Name(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr)
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
		cout << endl << endl << e.what() << dynamic_cast<Identifier*>(this->linkedMemberNonterminals.at(0))->getNodeTokenLineNumber()
			 << " Identifier Name: "     << dynamic_cast<Identifier*>(this->linkedMemberNonterminals.at(0))->getNodeTokenValue() << endl;
	}
	
}

void Name::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{
	//Defining as of 2/26/2021
	Token* currentToken = this->parserPtr->getCurrentlyReadToken();
	//printf("\nName_CurrentToken = %s", currentToken->getTokenValue().c_str());
	if (currentToken->getTokenType() == "IDENTIFIER")
	{
		this->linkedMemberNonterminals.push_back(new Identifier(currentToken, motherNode, "LOCAL", this));
		//recurse

	
		this->setIsValid(true);

	}

	else if (currentToken->getTokenValue() == "[")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
		//recurse
	}

	else if (tokenCounter == 1 && !(currentToken->getTokenValue() == "["))
	{
		if (currentToken->getTokenValue() == "("
		    )
		{
			this->setIsValid(false);
		}

	
		//We don't have a valid "[", so we return early, but it will still be set as valid, since the expression is optional.
		//We will have to back up the read index or this token will be ignored by furture methods.
		//this->parserPtr->resetTokenReadIndexToPrevious(); //Do not give it back.  We don't want it triggering other methods as it moves up the chain.
		//Identifier* ident = dynamic_cast<Identifier*>(this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1));
		/*if (ident != nullptr && ident->getNodeTokenType() == "IDENTIFIER")
		{
			//We have to back up the index again because it was stolen.
			this->parserPtr->resetTokenReadIndexToPrevious();
		}*/

		this->parserPtr->resetTokenReadIndexToPrevious();
		return;

	}

	

	else if (currentToken->getTokenValue() == "]")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
		//I believe here we need to consume the next token, since it messes other methods up.
		
		this->setIsValid(true);
		return;
	}

	else if (tokenCounter == 2)
	{
		//The option of having an expression here is optional, so if we don't have an expression, we need to get rid of the pointer
		//to the class within the parse tree, since it makes things more confusing.  First we have to add it to the tree and then check.

		this->linkedMemberNonterminals.push_back(new Expression(this->parserPtr, motherNode, this));
		bool isValid = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1)->getIsValid();
		if (!isValid)
		{
			this->linkedMemberNonterminals.pop_back();
			//We need to return here!  This is messing up everything and making me MAD!
			
		}

		//recurse

	}

	//Otherwise, we return.
	++tokenCounter;
	currentToken = this->parserPtr->readNextToken();
	this->verifySyntaxCreateParseTree(tokenCounter, motherNode);
	return;
}

ParseTreeNode* Name::getNodePtr()
{
	return this;

}

void Name::populateSearchResultsList(ParseTreeNode* motherNode)
{


	for (unsigned int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}

bool Name::checkIdentifierFollowsScopingRules()
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

void Name::checkArrayIndexIsIntegerLiteral(ParseTreeNode* numberNode)
{
	Number* number = nullptr;
	if ((number = dynamic_cast<Number*>(numberNode)) != nullptr)
	{
		if (number->getNumberTokenType() != "INTEGER_LITERAL")
		{
			//Throw an exception
			throw ArrayIndexNotAnIntegerLiteralException();
		}
		Identifier* ident = nullptr;
		if ((ident = dynamic_cast<Identifier*>(this->linkedMemberNonterminals.at(0))) != nullptr)
		{
			ident->setNumberPtrValue(number);

		}
	}
}
