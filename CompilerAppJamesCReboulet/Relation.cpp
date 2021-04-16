#include "Relation.h"
#include "Relation_.h"
#include "Term.h"
#include "Number.h"
#include "Identifier.h"
#include "StringLiteral.h"

//2-23-2021: Code needs to be modified.  This is type mark code.
Relation::Relation(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr)
{
	//Note: 3-13-2021: Added additional statement to set this node's parent node ptr, to enable reverse walking back up a tree.
	this->parentNodePtr = parentNodePtr;
	this->setParserPtr(parser);
	this->programNode_motherNode = motherNode;
	this->verifySyntaxCreateParseTree(0, motherNode);
	
}

void Relation::generateIntermediateCodeFromParseTree(ofstream* outputFileStream, vector<ParseTreeNode*>* declSymbolTablePtr)
{
	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->generateIntermediateCodeFromParseTree(outputFileStream, declSymbolTablePtr);
	}
}

void Relation::setIdentifierRelationPtrValue(ParseTreeNode* identifier)
{
	Identifier* ident = nullptr;
	if ((ident = dynamic_cast<Identifier*>(identifier)) != nullptr && this->identifierArithOpPtr == nullptr)
	{
		//If the pointer value has previously been set, do not reset it!
		this->identifierArithOpPtr = identifier;
	}
}

void Relation::setIdentifierRelation_PtrValue(ParseTreeNode* identifier)
{
	Identifier* ident = nullptr;
	if ((ident = dynamic_cast<Identifier*>(identifier)) != nullptr && this->identifierArithOp_Ptr == nullptr)
	{
		//If the pointer value has previously been set, do not reset it!
		this->identifierArithOp_Ptr = identifier;
	}
}

void Relation::setNumberRelationPtrValue(ParseTreeNode* numberToken)
{
	Number* num = nullptr;
	if ((num = dynamic_cast<Number*>(numberToken)) != nullptr && this->identifierArithOpPtr == nullptr)
	{
		//If the pointer value has previously been set, do not reset it!
		this->identifierArithOpPtr = num;
	}
}

void Relation::setNumberRelation_PtrValue(ParseTreeNode* numberToken)
{
	Number* num = nullptr;
	if ((num = dynamic_cast<Number*>(numberToken)) != nullptr && this->identifierArithOp_Ptr == nullptr)
	{
		//If the pointer value has previously been set, do not reset it!
		this->identifierArithOp_Ptr = num;
	}
}


void Relation::setStringLiteralRelationPtrValue(ParseTreeNode* stringLiteral)
{
	StringLiteral* str = nullptr;
	if ((str = dynamic_cast<StringLiteral*>(stringLiteral)) != nullptr && this->identifierArithOpPtr == nullptr)
	{
		//If the pointer value has previously been set, do not reset it!
		this->identifierArithOpPtr = str;
	}
}

void Relation::setStringLiteralRelation_PtrValue(ParseTreeNode* stringLiteral)
{
	StringLiteral* str = nullptr;
	if ((str = dynamic_cast<StringLiteral*>(stringLiteral)) != nullptr && this->identifierArithOp_Ptr == nullptr)
	{
		//If the pointer value has previously been set, do not reset it!
		this->identifierArithOp_Ptr = str;
	}
}

ParseTreeNode* Relation::getStringLiteralRelationPtrValue()
{
	return this->identifierArithOpPtr;
}

ParseTreeNode* Relation::getStringLiteralRelation_PtrValue()
{
	return this->identifierArithOp_Ptr;
}

ParseTreeNode* Relation::getIdentifierRelationPtrValue()
{
	return this->identifierArithOpPtr;
}

ParseTreeNode* Relation::getIdentifierRelation_PtrValue()
{
	return this->identifierArithOp_Ptr;
}

ParseTreeNode* Relation::getNumberRelationPtrValue()
{
	return this->identifierArithOpPtr;
}

ParseTreeNode* Relation::getNumberRelation_PtrValue()
{
	return this->identifierArithOp_Ptr;
}

void Relation::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{
	//Note:  This same code will now work with relation, term, and factor.  It just needs to be modified for each of those non-terminal classes.
	//If this->linkedMemberNonterminals happens to be empty, we don't want to do an access and pass a null pointer to the dynamic_cast method
	//That will probably cause a memory access violation to occur at runtime, because we are accessing a non-existent element in our vector.
	Token* currentToken = this->parserPtr->getCurrentlyReadToken();
	//printf("\nRelation_CurrentToken = %s", currentToken->getTokenValue().c_str());
	if (!this->linkedMemberNonterminals.empty() &&
		dynamic_cast<Term*>(this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1)) != nullptr)
	{
		this->linkedMemberNonterminals.push_back(new Relation_(this->parserPtr, motherNode, this));
		//Expression_ can possibly be empty, so if it is, we just remove it from the parse tree to eliminate confusion.
		bool isValid = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1)->getIsValid();
		if (!isValid)
		{
			this->linkedMemberNonterminals.pop_back();
			//Every time we get here, we need to give back the token, since a token gets burned up every time we arrive here.  It has to happen.
			//this->parserPtr->resetTokenReadIndexToPrevious();
			
			
		}

		//Note:  If we ever get here, we know that we have seen a correctly added ArithOp, so we set isValid(true);
		this->parserPtr->resetTokenReadIndexToPrevious();
		this->setIsValid(true);
		return;
	}

	else
	{
		
		this->linkedMemberNonterminals.push_back(new Term(this->parserPtr, motherNode, this));
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


	for (unsigned int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}
