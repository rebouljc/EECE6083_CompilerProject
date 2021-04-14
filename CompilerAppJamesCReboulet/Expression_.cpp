#include "Expression_.h"
#include "TerminalNode.h"
#include "Identifier.h"
#include "ArithOp.h"
#include "Expression.h"

//2-23-2021: Code needs to be modified.  This is type mark code.
Expression_::Expression_(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr)
{
	//Note: 3-13-2021: Added additional statement to set this node's parent node ptr, to enable reverse walking back up a tree.
	this->parentNodePtr = parentNodePtr;
	this->setParserPtr(parser);
	this->programNode_motherNode = motherNode;
	this->verifySyntaxCreateParseTree(0, motherNode);
	
}

void Expression_::generateIntermediateCodeFromParseTree(ifstream* outputFileStream)
{
	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->generateIntermediateCodeFromParseTree(outputFileStream);
	}
}

void Expression_::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{
	//Note:  This same code will now work with relation, term, and factor.  It just needs to be modified for each of those non-terminal classes.
	Token* currentToken = this->parserPtr->getCurrentlyReadToken();
	if (currentToken->getTokenValue() == "&" ||
		currentToken->getTokenValue() == "|")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
		
		Expression* expPtr = nullptr;

		

		if ((expPtr = dynamic_cast<Expression*>(this->parentNodePtr)) != nullptr)
		{
			//Do the flip flop here when "not" is present within an expression.  Changing the values of the numbers and identifiers will occur later.
			bool calledFromExpressionRef = true;
			bool parenthesesPresentFlag = false;
			bool expResult = expPtr->climbTreeAndCheckParenthesesPresentOnParentExpressionFlag(calledFromExpressionRef, parenthesesPresentFlag);

			if (expResult)
			{
				if (currentToken->getTokenValue() == "&")
				{
					currentToken->setTokenValue("|");
				}

				else if (currentToken->getTokenValue() == "|")
				{
					currentToken->setTokenValue("&");
				}
			}
		}
	}

	else if (currentToken->getTokenValue() == "not")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
	}

	//If this->linkedMemberNonterminals happens to be empty, we don't want to do an access and pass a null pointer to the dynamic_cast method
	//That will probably cause a memory access violation to occur at runtime, because we are accessing a non-existent element in our vector.
	else if (!this->linkedMemberNonterminals.empty() &&
		      dynamic_cast<ArithOp*>(this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1)) != nullptr)
	{
		this->linkedMemberNonterminals.push_back(new Expression_(this->parserPtr, motherNode, this));
		bool isValid = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1)->getIsValid();
		if (!isValid)
		{
			this->linkedMemberNonterminals.pop_back();

			//Every time we get here, we need to give back the token, since a token gets burned up every time we arrive here.  It has to happen.
			//this->parserPtr->resetTokenReadIndexToPrevious();
		}
		//If we ever get here, we can set the isValid flag to true, since we know we have had an ArithOp added at least.
		//No reason to check the size of the linkedMemberNonterminals each time and waste more CPU clock cycles and memory accesses.
		this->setIsValid(true);
		//UH! OH!  We had better return here, or we are going to get infinite recursion.
		return;
	}


	else if (!this->linkedMemberNonterminals.empty() &&
		dynamic_cast<TerminalNode*>(this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1)) != nullptr)
	{
		this->linkedMemberNonterminals.push_back(new ArithOp(this->parserPtr, motherNode, this));
		bool isValid = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1)->getIsValid();
		if (!isValid)
		{
			this->linkedMemberNonterminals.pop_back();
			//Here, we return early, since we assume that Expression_ is empty if we don't create a valid <ArithOp>.
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

ParseTreeNode* Expression_::getNodePtr()
{
	return this;

}

void Expression_::populateSearchResultsList(ParseTreeNode* motherNode)
{


	for (unsigned int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}
