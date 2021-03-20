#include "ParseTreeNode.h"
#include "Program.h"
#include "Declaration.h" //Every variable declared within a procedure header is 
                                  //local to ProcedureDeclaration
#include "ProcedureBody.h"
#include "Identifier.h"
#include "ProgramBody.h"
#include "ProcedureDeclaration.h"
#include "ProcedureHeader.h"
#include "Identifier.h"
#include "VariableDeclaration.h"



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

bool ParseTreeNode::addToSymbolTable(ParseTreeNode* symbolToAdd)
{
    bool match = false;
    

    for (vector<ParseTreeNode*>::iterator it = this->symbolTable.begin(); it < this->symbolTable.end(); ++it)
    {
        if (dynamic_cast<Identifier*>(*it)->getNodeTokenValue() ==
            dynamic_cast<Identifier*>(symbolToAdd)->getNodeTokenValue()
            )
        {
            match = true;
            break;
        }
    }

    if (!match && dynamic_cast<Identifier*>(symbolToAdd)->getIdentifierIsValidDeclaration())
    {
        this->symbolTable.push_back(symbolToAdd);
    }

    return !match;
}

bool ParseTreeNode::searchSymbolTable(ParseTreeNode* searchSymbol, ParseTreeNode* returnSymbol)
{
    
    for (vector<ParseTreeNode*>::iterator it = this->symbolTable.begin(); it < this->symbolTable.end(); ++it)
    {
        if (dynamic_cast<Identifier*>(*it)->getNodeTokenValue() ==
            dynamic_cast<Identifier*>(searchSymbol)->getNodeTokenValue()
            )
        {
            returnSymbol = dynamic_cast<Identifier*>(*it);
            return true;
        }
    }

    //We should never get here if the symbol is found in either a local or global table of a parseTree while climbing it.

    if (this->parentNodePtr == nullptr)
    {
        returnSymbol = nullptr;
        return false;
       
    }

    this->parentNodePtr->searchSymbolTable(searchSymbol, returnSymbol);

    
}
vector<ParseTreeNode*>* ParseTreeNode::getSymbolTable()
{
    return &(this->symbolTable);
}

void ParseTreeNode::climbTreeAndPopulateSymbolTable(string identifierType, ParseTreeNode* identifierNode)
{
  
    ParseTreeNode* decl;

    //Now, we can have local symbol tables for 
     //We reference our LOCAL symbol table to the "lowest hanging fruit" in our parseTree - i.e. whatever we encounter first,
        //since we have no clue where a given identifier will be placed in a given program's parse tree.
    if (this->parentNodePtr == nullptr)
    {
        
        return;
    }

    else if (identifierType == "GLOBAL")
    {
        this->programNode_motherNode->addToSymbolTable(identifierNode);
        return;
    }
  
    else if (identifierType == "LOCAL" || identifierType == "GLOBAL_EMBEDDED")
    {
        Identifier* ident = dynamic_cast<Identifier*>(identifierNode);
        
        if ((decl = dynamic_cast<Declaration*>(this)) != nullptr)
        {
            //This will check to see if a terminal node was created for "global" within the <declaration> parse subtree.

            if (decl->checkGlobalTerminalNodePresent())
            {
                identifierType = "GLOBAL";
                ident->setIdentifierTypeToGlobal();
                //We will keep climbing the tree until we hit the "GLOBAL" portion.
            }

            else if (identifierType == "GLOBAL_EMBEDDED")
            {
                //Kick the football up again so it will be caught by top declaration.
                identifierType ="LOCAL";
            }

            else 
            {
                this->addToSymbolTable(identifierNode);
                return;
            }
        }
        else if (dynamic_cast<VariableDeclaration*>(this) != nullptr)
        {
            if (dynamic_cast<ProgramBody*>(this->parentNodePtr->parentNodePtr) != nullptr)
            {
                identifierType = "GLOBAL";
                ident->setIdentifierTypeToGlobal();
                //Climb the tree again and this time, it will be caught correctly by the if (identifierType == "GLOBAL") statement.
            }

            else if (dynamic_cast<ProcedureBody*>(this->parentNodePtr->parentNodePtr) != nullptr)
            {
                identifierType = "GLOBAL_EMBEDDED";
            }
        }

        else if (dynamic_cast<ProcedureHeader*>(this) != nullptr)
        {
            if (dynamic_cast<ProcedureHeader*>(this)->getLinkedMemberNonterminalsSize() == 1 &&
                dynamic_cast<ProgramBody*>(this->parentNodePtr->parentNodePtr->parentNodePtr) != nullptr
                )
            {
                identifierType = "GLOBAL";
                ident->setIdentifierTypeToGlobal();
                //Keep climbing the tree and it will be caught by the if (identifierType == "GLOBAL") statement.

            }

            else if (dynamic_cast<ProcedureHeader*>(this)->getLinkedMemberNonterminalsSize() == 1)
            {
                identifierType = "GLOBAL_EMBEDDED";
            }

            //Otherwise, the variable is local and we climb the tree and it will be caught by declaration.
            //If the identifier happens to be global in declaration, the identifier/procedure type will be set to "GLOBAL"
        }

        
   
    }
   
    this->parentNodePtr->climbTreeAndPopulateSymbolTable(identifierType, identifierNode); //Do the recursive call here.
    return;
}