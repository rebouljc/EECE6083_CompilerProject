#include "Expression_.h"
#include "TerminalNode.h"
#include "Identifier.h"
#include "ArithOp.h"

//2-23-2021: Code needs to be modified.  This is type mark code.
Expression_::Expression_(Parser* parser, ParseTreeNode* motherNode)
{
	this->setParserPtr(parser);
	this->verifySyntaxCreateParseTree(0, motherNode);
}

void Expression_::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{
	//Note:  This same code will now work with relation, term, and factor.  It just needs to be modified for each of those non-terminal classes.
	Token* currentToken = this->parserPtr->getCurrentlyReadToken();
	if (currentToken->getTokenValue() == "&" ||
		currentToken->getTokenValue() == "|")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
	}

	else if (currentToken->getTokenValue() == "not")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
	}

	//If this->linkedMemberNonterminals happens to be empty, we don't want to do an access and pass a null pointer to the dynamic_cast method
	//That will probably cause a memory access violation to occur at runtime, because we are accessing a non-existent element in our vector.
	else if (!this->linkedMemberNonterminals.empty() &&
		      dynamic_cast<ArithOp*>(this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1)) != nullptr)
	{
		this->linkedMemberNonterminals.push_back(new Expression_(this->parserPtr, motherNode));
		bool isValid = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);
		if (!isValid)
		{
			this->linkedMemberNonterminals.pop_back();
		}
		//If we ever get here, we can set the isValid flag to true, since we know we have had an ArithOp added at least.
		//No reason to check the size of the linkedMemberNonterminals each time and waste more CPU clock cycles and memory accesses.
		this->setIsValid(true);
		//UH! OH!  We had better return here, or we are going to get infinite recursion.
		return;
	}


	else
	{
		this->linkedMemberNonterminals.push_back(new ArithOp(this->parserPtr, motherNode));
		bool isValid = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);
		if (!isValid)
		{
			this->linkedMemberNonterminals.pop_back();
			//Here, we return early, since we assume that Expression_ is empty if we don't create a valid <ArithOp>.
			//We have to stop the infinite recursion from occurring.
			return;
			
		}
		
	}

	currentToken = this->parserPtr->readNextToken();
	++tokenCounter;
	this->verifySyntaxCreateParseTree(tokenCounter, motherNode);
	return;
}

ParseTreeNode* Expression_::getNodePtr()
{
	return this;

}

void Expression_::populateSearchResultsList(ParseTreeNode* motherNode)
{


	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}