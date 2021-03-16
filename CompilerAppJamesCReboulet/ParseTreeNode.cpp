#include "ParseTreeNode.h"
#include "Program.h"
#include "Declaration.h" //Every variable declared within a procedure header is 
                                  //local to ProcedureDeclaration
#include "ProcedureBody.h"
#include "Identifier.h"



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

    if (!match)
    {
        this->symbolTable.push_back(symbolToAdd);
    }

    return !match;
}

ParseTreeNode* ParseTreeNode::searchSymbolTable(ParseTreeNode* searchSymbol)
{
    for (vector<ParseTreeNode*>::iterator it = this->symbolTable.begin(); it < this->symbolTable.end(); ++it)
    {
        if (dynamic_cast<Identifier*>(*it)->getNodeTokenValue() ==
            dynamic_cast<Identifier*>(searchSymbol)->getNodeTokenValue()
            )
        {

            return *it;
        }
    }

    return nullptr;
}
vector<ParseTreeNode*>* ParseTreeNode::getSymbolTable()
{
    return &(this->symbolTable);
}

void ParseTreeNode::climbTreeAndPopulateSymbolTable(string identifierType, ParseTreeNode* identifierNode)
{
  
    ParseTreeNode* decl;
    if (this->parentNodePtr == nullptr)
    {
        this->addToSymbolTable(identifierNode);
        return;
    }

    else if (identifierType == "GLOBAL" && dynamic_cast<Program*>(this) != nullptr)
    {
        //We have a PROGRAM and the variable is global, so it is placed in the GLOBAL symbol table.
        //This either occurs if the identifier is labeled "GLOBAL"
        this->addToSymbolTable(identifierNode);
        return;
       
    }

    //Now, we can have local symbol tables for 
     //We reference our LOCAL symbol table to the "lowest hanging fruit" in our parseTree - i.e. whatever we encounter first,
        //since we have no clue where a given identifier will be placed in a given program's parse tree.
    else if (identifierType == "LOCAL")
    {
        if (dynamic_cast<Program*>(this) != nullptr)
        {
            this->addToSymbolTable(identifierNode);
            return;
        }
        
        else if ((decl = dynamic_cast<Declaration*>(this)) != nullptr)
        {
            ParseTreeNode* checkParent;

            if ((checkParent = dynamic_cast<Program*>(this->parentNodePtr)) != nullptr)
            {
                checkParent->addToSymbolTable(identifierNode); //Here, we have a global variable.
            }

            //This will check to see if a terminal node was created for "global" within the <declaration> parse subtree.

            else if (decl->checkGlobalTerminalNodePresent()) 
            {
                decl->programNode_motherNode->addToSymbolTable(identifierNode);
            }

            else
            {
                this->addToSymbolTable(identifierNode);
            }
           
            return;
        }

        else if (dynamic_cast<ProcedureBody*>(this) != nullptr)
        {
            //We have an identifier that is local to PROCEDURE DECLARATION.  It is declared within the 
            //PROCEDURE HEADER. 
            this->addToSymbolTable(identifierNode);
            return;
            
        }
        

        

    }
   
    this->parentNodePtr->climbTreeAndPopulateSymbolTable(identifierType, identifierNode); //Do the recursive call here.
    return;
}