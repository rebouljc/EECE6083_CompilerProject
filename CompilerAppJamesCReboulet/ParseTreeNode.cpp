#include "ParseTreeNode.h"
#include "Program.h"
#include "ProcedureDeclaration.h" //Every variable declared within a procedure header is 
                                  //local to ProcedureDeclaration
#include "ProcedureBody.h"



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

void ParseTreeNode::climbTreeAndPopulateSymbolTable(int identifierId, string identifierType, ParseTreeNode* identifierNode)
{
    if (this->parentNodePtr == nullptr)
    {
        //The object is a <Program> object, since its pointer is always null, so we set the identifier as global.
        //This identifier is added to the global symbol table for PROGRAM.

    }
    else if (dynamic_cast<Program*>(this->parentNodePtr) != nullptr && identifierType == "GLOBAL")
    {
        //We have a PROGRAM and the variable is global, so it is placed in the GLOBAL symbol table.
        //This either occurs if the identifier is labeled "GLOBAL"
    }

    //Now, we can have local symbol tables for 
    else if (identifierType != "GLOBAL")
    {
        //We reference our LOCAL symbol table to the "lowest hanging fruit" in our parseTree - i.e. whatever we encounter first,
        //since we have no clue where a given identifier will be placed in a given program's parse tree.
        if (dynamic_cast<ProcedureDeclaration*>(this->parentNodePtr) != nullptr)
        {
            //We have an identifier that is local to PROCEDURE DECLARATION.  It is declared within the 
            //PROCEDURE HEADER.  

        }

        else if (dynamic_cast<ProcedureBody*>(this->parentNodePtr) != nullptr)
        {
            //The identifier comes from somewhere in PROCEDURE BODY and is local to PROCEDURE BODY.
            //This is the lowest hanging fruit in a procedure in the design of the parse tree.
        }
       
    }

}