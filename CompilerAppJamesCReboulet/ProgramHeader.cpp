#include "ProgramHeader.h"
#include "Identifier.h"

ProgramHeader::ProgramHeader(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr)
{
	//Note: 3-13-2021: Added additional statement to set this node's parent node ptr, to enable reverse walking back up a tree.
	this->parentNodePtr = parentNodePtr;
	this->setParserPtr(parser);
	this->programNode_motherNode = motherNode;
	this->verifySyntaxCreateParseTree(0, motherNode);
	
}

void ProgramHeader::generateIntermediateCodeFromParseTree(ofstream* outputFileStream, vector<ParseTreeNode*>* declSymbolTablePtr)
{
	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->generateIntermediateCodeFromParseTree(outputFileStream, declSymbolTablePtr);
	}
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
				this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this)); //TerminalNode inherits from both ParseTreeNode and Token.  
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
				this->linkedMemberNonterminals.push_back(new Identifier(currentToken, motherNode, "LOCAL", this));
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
				this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
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
	
	
	for (unsigned int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(this);

	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}
