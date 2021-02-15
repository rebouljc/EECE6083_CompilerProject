#include "TerminalNode.h"

TerminalNode::TerminalNode(Token* token)
{
	this->token = token;
							 
}

TerminalNode::TerminalNode(Token* token, ParseTreeNode* motherNode, string identifierType)
{
	this->token = token;
	//If this constructor is called, this terminal node is an <identifier>
	bool alreadyInTable = false;
	for (int i = 0; i < motherNode->getSymbolTable()->size(); ++i)
	{
		TerminalNode* currentNode = dynamic_cast<TerminalNode*>(motherNode->getSymbolTable()->at(i));
		if (currentNode->getNodeTokenValue() == token->getTokenValue())
		   
		{
			if (currentNode->getNodeSymbolIdentifierType() == "GLOBAL")
			{
				//Throw the exception!  We have a redeclaration of a global variable which is bad.
				//We do nothing for now, but this will be a future exception.
			}
			alreadyInTable = true;
			break;
		}
		
	}

	if (!alreadyInTable)
	{
		
		motherNode->addToSymbolTable((ParseTreeNode*)this);
	}

	this->identifierType = identifierType;
}

//Now, we will add a couple of duplicate methods from Token* here to streamline the process.  There are a lot of unnecessary public methods in token 
//that are not needed here and may make things confusing.

string TerminalNode::getNodeTokenType()
{
	return this->token->getTokenType();
}
string TerminalNode::getNodeTokenValue()
{
	return this->token->getTokenValue();
}

string TerminalNode::getNodeSymbolIdentifierType()
{
	return this->identifierType;
}
double TerminalNode::getNodeTokenIntegerDoubleNumberTokenValue()
{
	return this->token->getIntegerDoubleNumberTokenValue();
}
int TerminalNode::getNodeTokenLineNumber()
{
	return this->token->getTokenLineNumber();
}

ParseTreeNode* TerminalNode::getNodePtr()
{
	return this;

}

void TerminalNode::populateSearchResultsList(ParseTreeNode* motherNode)
{
	motherNode->addToSearchResultsList(this->getNodePtr());
}



