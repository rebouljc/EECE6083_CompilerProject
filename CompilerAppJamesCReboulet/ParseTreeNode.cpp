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
        ++ this->indexToRead;
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

void ParseTreeNode::addToSymbolTable(ParseTreeNode* nodeToAdd)
{
    this->symbolTable.push_back(nodeToAdd);
}
vector<ParseTreeNode*>* ParseTreeNode::getSymbolTable()
{
    return &(this->symbolTable);
}