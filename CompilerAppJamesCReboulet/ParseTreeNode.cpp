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

void ParseTreeNode::searchAndAddIdentifierToLocalSymbolTable(ParseTreeNode* localObjectPtr)
{
    //We search for the identifier and if we find one, we get its terminal symbol and its token and add it to the 
    //local symbol table.  When we arrive at the pointer that matches the typeid of whatever class is in localObjectPtr,
    //we terminate the loop and return.  Placing it here makes the process easier, since I only have to put this method
    //in one place and it saves coding and debugging time.

}