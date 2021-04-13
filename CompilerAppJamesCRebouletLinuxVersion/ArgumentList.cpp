#include "ArgumentList.h"
#include "TerminalNode.h"
#include "Expression.h"



//2-23-2021: Code needs to be modified.  This is type mark code.
ArgumentList::ArgumentList(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr)
{
	//Note: 3-13-2021: Added additional statement to set this node's parent node ptr, to enable reverse walking back up a tree.
	this->parentNodePtr = parentNodePtr;
	this->setParserPtr(parser);
	this->programNode_motherNode = motherNode;
	this->verifySyntaxCreateParseTree(0, motherNode);
	
}

void ArgumentList::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{
	//We modified this from the code taken from the <Name> class. These changes are as of 2/28/2021.
	//Originally destination was defined on 2/26/2021.

	Token* currentToken = parserPtr->getCurrentlyReadToken();
	//printf("\nArgumentList_CurrentToken = %s", currentToken->getTokenValue().c_str());

	//We have to make sure this->linkedMemberNonterminals is not empty, or else we will get a memory access violation, crash and burn.
	//Lazy way to do this, but it will work.  We want to make sure that the last character added was a "Terminal Symbol" and it was a ","

	if (currentToken->getTokenValue() == ",")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken,this));
		//recurse

	}

	else if (!this->linkedMemberNonterminals.empty() &&
		     dynamic_cast<TerminalNode*>(this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1)) != nullptr
		     )
	{
		this->linkedMemberNonterminals.push_back(new ArgumentList(this->parserPtr, motherNode, this));
		//recurse
	}

	else if (this->linkedMemberNonterminals.empty())
	{
		//We only add expressions when this->linkedMemberNonterminals.empty().  Otherwise, we have recursed back here from HERE, and we don't
		//want to keep coming back here until we blow the stack.

		this->linkedMemberNonterminals.push_back(new Expression(this->parserPtr, motherNode, this));
		bool isValid = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1)->getIsValid();
		if (!isValid)
		{
			this->linkedMemberNonterminals.pop_back();
			//We need to return here, if we do not have a valid expression, we also do not have a valid <argument_list>.
			//We return with this->isValid = false; .
			return;
		}

		//Otherwise, we recurse.  We will get a "," followed by an <Argument_List>

	}

	else
	{
		//We have to return if we don't have a ","  What if a "cigar is just a cigar" but "it is just an unlit cigar"?  We end up here and return!
		//We are assuming that we have just an <expression> for the <Argument_List>.  We have to prevent the infinite recursion if this is the case
		//Or we will keep recursing at <Expression> for ever because we eventually come back to <Argument_List> from <Expression> and keep going..
		this->setIsValid(true);
		return;
	}


	//Otherwise, we return.
	++tokenCounter;
	currentToken = this->parserPtr->readNextToken();
	this->verifySyntaxCreateParseTree(tokenCounter, motherNode);
	return;
}

ParseTreeNode* ArgumentList::getNodePtr()
{
	return this;

}

void ArgumentList::populateSearchResultsList(ParseTreeNode* motherNode)
{


	for (unsigned int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}
