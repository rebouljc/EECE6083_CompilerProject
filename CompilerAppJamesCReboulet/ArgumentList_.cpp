#include "ArgumentList_.h"
#include "ArgumentList.h"
#include "TerminalNode.h"
#include "Expression.h"



//2-23-2021: Code needs to be modified.  This is type mark code.
ArgumentList_::ArgumentList_(Parser* parser, ParseTreeNode* motherNode)
{
	this->setParserPtr(parser);
	this->verifySyntaxCreateParseTree(0, motherNode);
}

void ArgumentList_::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{
	//We modified this from the code taken from the <Name> class. These changes are as of 2/28/2021.
	//Originally destination was defined on 2/26/2021.

	Token* currentToken = parserPtr->getCurrentlyReadToken();

	//We have to make sure this->linkedMemberNonterminals is not empty, or else we will get a memory access violation, crash and burn.
	//Lazy way to do this, but it will work.  We want to make sure that the last character added was a "Terminal Symbol" and it was a ","

	if (currentToken->getTokenValue() == ",")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));

	}

	else if (dynamic_cast<TerminalNode*>(this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1)) != nullptr)
	{
		this->linkedMemberNonterminals.push_back(new ArgumentList(this->parserPtr, motherNode));
		//recurse
	}

	else if (dynamic_cast<ArgumentList*>(this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1)) != nullptr)
	{
		this->linkedMemberNonterminals.push_back(new ArgumentList_(this->parserPtr, motherNode));
	}

	else
	{
		this->linkedMemberNonterminals.push_back(new Expression(this->parserPtr, motherNode));
		bool isValid = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);
		if (!isValid)
		{
			this->linkedMemberNonterminals.pop_back();
			//We need to return here, if we do not have a valid expression, we also do not have a valid <argument_list>.
			//We return with this->isValid = false; .
			return;
		}


		this->setIsValid(true);

		//Otherwise, we recurse.  We will get a "," followed by an <Argument_List>

	}

	//Otherwise, we return.
	++tokenCounter;
	currentToken = this->parserPtr->readNextToken();
	this->verifySyntaxCreateParseTree(tokenCounter, motherNode);
	return;
}

ParseTreeNode* ArgumentList_::getNodePtr()
{
	return this;

}

void ArgumentList_::populateSearchResultsList(ParseTreeNode* motherNode)
{


	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}