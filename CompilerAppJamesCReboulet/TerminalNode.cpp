#include "TerminalNode.h"
#include "TypeMark.h"



TerminalNode::TerminalNode()
{
	this->token = nullptr;
}

TerminalNode::TerminalNode(Token* token, ParseTreeNode* parentNodePtr)
{
	//Note: 3-13-2021: Added additional statement to set this node's parent node ptr, to enable reverse walking back up a tree.
	this->parentNodePtr = parentNodePtr;
	this->token = token;
							 
}

void TerminalNode::generateIntermediateCodeFromParseTree(ofstream* outputFileStream)
{
	TypeMark* typeMark = nullptr;
	if (dynamic_cast<TypeMark*>(this->parentNodePtr) != nullptr)
	{
		if (this->getNodeTokenValue() == "integer")
		{
			(*outputFileStream) << " i32";
		}
	}
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

void TerminalNode::setNodeTokenValue(std::string value)
{
	this->token->setTokenValue(value);
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




