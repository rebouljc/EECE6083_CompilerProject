#include "ArithOp_.h"
#include "TerminalNode.h"
#include "Relation.h"
#include "Identifier.h"

//2-23-2021: Code needs to be modified.  This is type mark code.
ArithOp_::ArithOp_(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr)
{
	//Note: 3-13-2021: Added additional statement to set this node's parent node ptr, to enable reverse walking back up a tree.
	this->parentNodePtr = parentNodePtr;
	this->setParserPtr(parser);
	this->programNode_motherNode = motherNode;
	this->verifySyntaxCreateParseTree(0, motherNode);
	
}


void ArithOp_::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{
	//Note:  This same code will now work with relation, term, and factor.  It just needs to be modified for each of those non-terminal classes.
	Token* currentToken = this->parserPtr->getCurrentlyReadToken();
	if (currentToken->getTokenValue() == "+" ||
		currentToken->getTokenValue() == "-")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
	}

	//If this->linkedMemberNonterminals happens to be empty, we don't want to do an access and pass a null pointer to the dynamic_cast method
	//That will probably cause a memory access violation to occur at runtime, because we are accessing a non-existent element in our vector.
	else if (!this->linkedMemberNonterminals.empty() &&
		      dynamic_cast<Relation*>(this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1)) != nullptr)
	{
		this->linkedMemberNonterminals.push_back(new ArithOp_(this->parserPtr, motherNode, this));
		bool isValid = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1)->getIsValid();
		if (!isValid)
		{
			this->linkedMemberNonterminals.pop_back();
			//Try giving back the value. 
			//this->parserPtr->resetTokenReadIndexToPrevious();
			//Every time we get here, we need to give back the token, since a token gets burned up every time we arrive here.  It has to happen.
			//this->parserPtr->resetTokenReadIndexToPrevious();
		}
		//If we ever get here, we can set the isValid flag to true, since we know we have had an ArithOp added at least.
		//No reason to check the size of the linkedMemberNonterminals each time and waste more CPU clock cycles and memory accesses.
		
		this->setIsValid(true);
		
		
		//UH! OH!  We had better return here, or we are going to get infinite recursion.
		return;
	}


	else if(!this->linkedMemberNonterminals.empty() &&
		     dynamic_cast<TerminalNode*>(this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1)) != nullptr)
	{
		
		this->linkedMemberNonterminals.push_back(new Relation(this->parserPtr, motherNode, this));
		bool isValid = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1)->getIsValid();
		if (!isValid)
		{
			this->linkedMemberNonterminals.pop_back();
			//Here, we return early, since we assume that ArithOp_ is empty if we don't create a valid <ArithOp>.
			//We have to stop the infinite recursion from occurring.
			return;

		}
		
		
		

	}
	else
	{
		return;
	}

	currentToken = this->parserPtr->readNextToken();
	++tokenCounter;
	this->verifySyntaxCreateParseTree(tokenCounter, motherNode);
	return;
}

ParseTreeNode* ArithOp_::getNodePtr()
{
	return this;

}

void ArithOp_::populateSearchResultsList(ParseTreeNode* motherNode)
{


	for (unsigned int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}