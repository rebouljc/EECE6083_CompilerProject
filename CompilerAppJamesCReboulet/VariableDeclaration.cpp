#include "VariableDeclaration.h"
#include "Token.h"
#include "TerminalNode.h"
#include "Identifier.h"
#include "TypeMark.h"
#include "Bound.h"  //This is used instead of Parameter List;


VariableDeclaration::VariableDeclaration(Parser* parser, ParseTreeNode* motherNode)
{
	this->setParserPtr(parser);
	this->verifySyntaxCreateParseTree(0, motherNode);
}

void VariableDeclaration::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{   //Same as ProcedureDeclaration::verifySyntaxCreateParseTree() method, except "variable" is used, and <bound> is substituted for 
	//<parameter_list>.

	  //Needs to be modified for program body.  Make it recursive to handle multiple declarations and statements.
	//Read the next token here.
		Token* currentToken = parserPtr->getCurrentlyReadToken();
		if (tokenCounter == 0)
		{
			if (currentToken->getTokenValue() == "variable")
			{
				this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
			}

			else
			{
				this->setIsValid(false);
				return;
			}

		}
		else if (tokenCounter == 1)
		{
			if (currentToken->getTokenType() == "IDENTIFIER")
			{
				this->linkedMemberNonterminals.push_back(new Identifier(currentToken, motherNode, "GLOBAL"));
			}

			else
			{
				//Throw an exception and return.
				return;
			}

		}
		else if (tokenCounter == 2)
		{
			if (currentToken->getTokenValue() == ":")
			{
				this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
			}

			else
			{
				//Throw an exception and return.
				return;
			}

		}

		else if (tokenCounter == 3) //If it is equal to 3 and we have made it this far, we need a type mark.
		{
			this->linkedMemberNonterminals.push_back(new TypeMark(this->parserPtr, motherNode));
		}

		else if (tokenCounter == 4)
		{
			if (currentToken->getTokenValue() == "[")
			{
				this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
			}

			else
			{
				//Throw an exception.
				return;
			}
		}

		else if (tokenCounter == 5)
		{
			this->linkedMemberNonterminals.push_back(new Bound(currentToken, this->parserPtr, motherNode));
			//If there are no parameters, then pop_back() the vector.
		}

		else if (tokenCounter == 6)
		{
			if (currentToken->getTokenValue() == "]")
			{
				this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
			}

			else
			{
				//Throw an exception and return;

			}

			//Right here, we return now, if this recursive method is complete.
			return;
		}

		++tokenCounter;
		//Read in the next token now, if we get here, before recursion.
		currentToken = parserPtr->readNextToken();
		this->verifySyntaxCreateParseTree(tokenCounter, motherNode);
		return;

	

}


ParseTreeNode* VariableDeclaration::getNodePtr()
{
	return this;

}

void VariableDeclaration::populateSearchResultsList(ParseTreeNode* motherNode)
{


	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}