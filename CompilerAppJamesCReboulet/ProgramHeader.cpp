#include "ProgramHeader.h"
#include "Identifier.h"

ProgramHeader::ProgramHeader(Parser* parser, ParseTreeNode* motherNode)
{
	this->setParserPtr(parser);
	this->verifySyntaxCreateParseTree(0, motherNode);
}

void ProgramHeader::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{
	Token* currentToken = this->parserPtr->readNextToken();
	if (currentToken != nullptr)
	{
		//Note:  We need to throw the applicable exceptions if we don't get what is expected
		//check to see that the first token equals "Program"
		if (tokenCounter == 0)
		{
			if (currentToken->getTokenValue() == "program")
			{
				this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken)); //TerminalNode inherits from both ParseTreeNode and Token.  
			}

			else
			{
				return;  //Return for now, throw exception later.
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
				return;  //Return for now, throw exception later.
			}
		}

		else if (tokenCounter == 2)
		{
			if (currentToken->getTokenValue() == "is")
			{
				this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken));
				return;
			}

			else
			{
				return;  //Return for now, throw exception later.
			}
		}
		++tokenCounter;
		this->verifySyntaxCreateParseTree(tokenCounter, motherNode);
	}

	return;
}

ParseTreeNode* ProgramHeader::getNodePtr()
{
	return this;

}

void ProgramHeader::populateSearchResultsList(ParseTreeNode* motherNode)
{
	

	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}