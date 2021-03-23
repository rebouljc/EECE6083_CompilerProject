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
#include "GlobalIdentifierIsNotUniqueException.h"
#include "Destination.h"
#include "ArrayIndexNotAnIntegerLiteralException.h"
#include "Number.h"


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

bool ParseTreeNode::addToSymbolTable(ParseTreeNode* symbolToAdd, bool checkUnique)
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

    else if (match && checkUnique)
    {
        //We throw an exception.  Global Identifiers must be unique.
        throw GlobalIdentifierIsNotUniqueException();
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
    try
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

            this->programNode_motherNode->addToSymbolTable(identifierNode, true);
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
                    identifierType = "LOCAL";
                }

                else
                {
                    decl->addToSymbolTable(identifierNode, false);
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
    }
        catch (GlobalIdentifierIsNotUniqueException& e)
        {
            cout << endl << endl << e.what() << dynamic_cast<Identifier*>(identifierNode)->getNodeTokenLineNumber()
                << " Identifier Name: " << dynamic_cast<Identifier*>(identifierNode)->getNodeTokenValue() << endl;
            return;
        }
    
    //recurse
    this->parentNodePtr->climbTreeAndPopulateSymbolTable(identifierType, identifierNode); //Do the recursive call here.
    return;
}

void ParseTreeNode::climbTreeAndVerifyArrayIndices(ParseTreeNode* numberNode)
{
    try
    {
        Destination* dest = nullptr;

        if (this->parentNodePtr == nullptr)
        {
            return;
        }

        else if ((dest = dynamic_cast<Destination*>(this)) != nullptr)
        {
            //We are currently at <Destination*> non-terminal, and we have to check to see if we have an expression.
            //We search the non-terminals.
            vector<ParseTreeNode*> resultList = dest->getLinkedMemberNonterminalsList();
            for (int i = 0; i < resultList.size(); ++i)
            {
                TerminalNode* termNode = nullptr;
                if ((termNode = dynamic_cast<TerminalNode*>(resultList.at(i))) != nullptr && termNode->getNodeTokenValue() == "[")
                {
                    dest->checkArrayIndexIsIntegerLiteral(numberNode);
                }
            }

        }

        //Now, we have to climb the tree until we reach a <VariableDeclaration>.  We then search for a <bound> non-terminal and 
        //We have bounds do a bounds check.  But we have to add a method to access its linkedMemberNonterminalsList() first.
        //Then, we add a method to do the bounds check.  That method will throw an exception and arrive here if bounds is out of range.
        //We will catch it here and report the results.
    }
    catch (ArrayIndexNotAnIntegerLiteralException& e)
    {
        cout << endl << endl << e.what() << dynamic_cast<Number*>(numberNode)->getNodeTokenLineNumber();
        return;
    }
    //recurse
    this->parentNodePtr->climbTreeAndVerifyArrayIndices(numberNode);
}

void ParseTreeNode::climbTreeAndPerformArrayBoundsCheck(ParseTreeNode* numberNode, ParseTreeNode* identifierNode)
{
    
}

vector<ParseTreeNode*>& ParseTreeNode::getLinkedMemberNonterminalsList()
{
    return this->linkedMemberNonterminals;
}