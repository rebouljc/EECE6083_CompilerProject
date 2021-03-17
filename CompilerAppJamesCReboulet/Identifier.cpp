#include "Identifier.h"

Identifier::Identifier(Token* token, ParseTreeNode* motherNode, string identifierType, ParseTreeNode* parentNodePtr)
{
	//Note: 3-13-2021: Added additional statement to set this node's parent node ptr, to enable reverse walking back up a tree.
	this->parentNodePtr = parentNodePtr;
	this->token = token;
	this->programNode_motherNode = motherNode;
	this->identifierType = identifierType;
	this->climbTreeAndPopulateSymbolTable(this->identifierType, this);
	

}

void Identifier::setIdentifierTypeToGlobal()
{
	this->identifierType = "GLOBAL";
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

