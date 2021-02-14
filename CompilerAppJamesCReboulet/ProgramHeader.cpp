#include "ProgramHeader.h"
#include "TerminalNode.h"

ProgramHeader::ProgramHeader(Parser* parser)
{
	this->setParserPtr(parser);
	this->verifySyntaxCreateParseTree();
}

void ProgramHeader::verifySyntaxCreateParseTree()
{
	Token* currentToken = this->readNextToken();
	if (currentToken != nullptr)
	{
		//check to see that the first token equals "Program"
		if (currentToken->getTokenValue() == "program")
		{
			this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken)); //TerminalNode inherits from both ParseTreeNode and Token.  
		}

	}

}

ParseTreeNode* ProgramHeader::getNodePtr()
{
	return this;

}

void ProgramHeader::populateSearchResultsList(ParseTreeNode* motherNode)
{
	motherNode->addToSearchResultsList(this->getNodePtr());

	for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}
}