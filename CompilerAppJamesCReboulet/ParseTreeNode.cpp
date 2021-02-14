#include "ParseTreeNode.h"

vector<ParseTreeNode*>* ParseTreeNode::getSearchResultsList(ParseTreeNode* currentProgramNodePtr)
{
    currentProgramNodePtr->populateSearchResultsList();
    return &(this->searchResultsList);
}
void ParseTreeNode::addToSearchResultsList(ParseTreeNode* nodeToAdd)
{
    this->searchResultsList.push_back(nodeToAdd);
}
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