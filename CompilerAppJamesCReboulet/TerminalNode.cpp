#include "TerminalNode.h"

TerminalNode::TerminalNode()
{

}
TerminalNode::TerminalNode(Token* token)
{
	this->token = token;
							 
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



