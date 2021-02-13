#include "ParseTreeNode.h"


Token* ParseTreeNode::readNextToken()
{   
    Token* tokToReturn;
    if (this->indexToRead < this->parserPtr->getStoredTokensList()->size())
    {
        tokToReturn = this->parserPtr->getStoredTokensList()->at(this->indexToRead);
    }

    else
    {
        tokToReturn = nullptr;
    }
    
    return tokToReturn;
   

}

void ParseTreeNode::setParserPtr(Parser* parserPtr)
{
    this->parserPtr = parserPtr;
}