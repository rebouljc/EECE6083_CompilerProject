#include "Identifier.h"

Identifier::Identifier(Token* token, ParseTreeNode* motherNode, string identifierType)
{
	this->token = token;
	//If this constructor is called, this terminal node is an <identifier>
	bool alreadyInTable = false;
	for (int i = 0; i < motherNode->getSymbolTable()->size(); ++i)
	{
		Identifier* currentNode = dynamic_cast<Identifier*>(motherNode->getSymbolTable()->at(i));
		if (currentNode->getNodeTokenValue() == token->getTokenValue() &&
			currentNode->getNodeSymbolIdentifierType() == "GLOBAL")

		{
			/*if (currentNode->getNodeSymbolIdentifierType() == "GLOBAL")
			{
				//Throw the exception!  We have a redeclaration of a global variable which is bad.
				//We do nothing for now, but this will be a future exception.
			}*/
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

string Identifier::getNodeSymbolIdentifierType()
{
	return this->identifierType;
}

ParseTreeNode* Identifier::getNodePtr()
{
	return this;

}

void Identifier::populateSearchResultsList(ParseTreeNode* motherNode)
{
	motherNode->addToSearchResultsList(this->getNodePtr());
}
