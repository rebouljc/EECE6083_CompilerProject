#include "Relation.h"
#include "Relation_.h"
#include "Term.h"

//2-23-2021: Code needs to be modified.  This is type mark code.
Relation::Relation(Parser* parser, ParseTreeNode* motherNode)
{
	this->setParserPtr(parser);
	this->verifySyntaxCreateParseTree(0, motherNode);
}

void Relation::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{
	//Note:  This same code will now work with relation, term, and factor.  It just needs to be modified for each of those non-terminal classes.
	//If this->linkedMemberNonterminals happens to be empty, we don't want to do an access and pass a null pointer to the dynamic_cast method
	//That will probably cause a memory access violation to occur at runtime, because we are accessing a non-existent element in our vector.
	Token* currentToken = this->parserPtr->getCurrentlyReadToken();

	if (!this->linkedMemberNonterminals.empty() &&
		dynamic_cast<Term*>(this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1)) != nullptr)
	{
		this->linkedMemberNonterminals.push_back(new Relation_(this->parserPtr, motherNode));
		//Expression_ can possibly be empty, so if it is, we just remove it from the parse tree to eliminate confusion.
		bool isValid = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1)->getIsValid();
		if (!isValid)
		{
			this->linkedMemberNonterminals.pop_back();
		}

		//Note:  If we ever get here, we know that we have seen a correctly added ArithOp, so we set isValid(true);
		this->setIsValid(true);
		return;
	}

	else
	{
		this->linkedMemberNonterminals.push_back(new Term(this->parserPtr, motherNode));
		bool isValid = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1)->getIsValid();
		if (!isValid)
		{
			this->linkedMemberNonterminals.pop_back();
			//Here, we return early, since there is no reason to continue if we don't have an arithOp.  It is a waste of resources.
			return;
		}

	}

	currentToken = this->parserPtr->readNextToken();
	++tokenCounter;
	this->verifySyntaxCreateParseTree(tokenCounter, motherNode);
}

ParseTreeNode* Relation::getNodePtr()
{
	return this;

}

void Relation::populateSearchResultsList(ParseTreeNode* motherNode)
{


	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}