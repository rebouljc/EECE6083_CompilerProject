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
#include "Bound.h"
#include "ArrayIndexOutOfBoundsException.h"
#include "Name.h"
#include "ArithOp.h"
#include "ArithOp_.h"
#include "TypeMark.h"
#include "Program.h"
#include "Declaration.h"
#include "Term.h"
#include "Term_.h"
#include "Expression.h"
#include "Expression_.h"
#include "ExpressionOperatorsAreNotAValidTypeException.h"



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

void ParseTreeNode::climbTreeAndVerifyArithmeticOperationsAreCorrectlyDefined(ParseTreeNode* tokenToCompare, bool numberSet)
{
    //Identifier and Number will call this method.
    //Then ArithOp_ will call this method.
    ArithOp_* arithOp_Ptr = nullptr;
    ArithOp* arithOpPtr = nullptr;
    Declaration* declPtr = nullptr;
    Identifier* identifierArithOpPtr = nullptr;
    Identifier* identifierArithOp_Ptr = nullptr;
    

    
    if (this->parentNodePtr == nullptr)
    {
        return;
    }
    else if ((arithOpPtr = dynamic_cast<ArithOp*>(this)) != nullptr)
    {
        //Identifier will set its ArithOpPtr to arithOpPtr.
        if (dynamic_cast<Number*>(tokenToCompare) != nullptr && !numberSet)
        {
            arithOpPtr->setNumberArithOpPtrValue(tokenToCompare);
        }
        else if (dynamic_cast<Identifier*>(tokenToCompare) != nullptr)
        {
            arithOpPtr->setIdentifierArithOpPtrValue(tokenToCompare);
        }
        
        //If both ArithOp ptr values are not equal to nullptr, we will continue to climb the tree to declaration.
        //When we get there, we will do the type checking portion.
        //We have to pass both pointers up to <Declaration>, search <Declaration> for the respective Identifier
        //and then do the check.  
        //We will start this either late tomorrow or on Monday, since I have another project to work on tomorrow after 
        //I am finally able to go to church with mask, since I received my first dose of the COVID-19 Pfizer vaccine!
        //I still wear a KN-95 mask though, until the week following my second dose.  Then I will downgrade to a cloth mask.

        ParseTreeNode* tokenToCompareLeft = nullptr;
        ParseTreeNode* tokenToCompareRight = nullptr;
        bool leftTokInserted = false;
        bool rightTokInserted = false;
        bool expressionPresentFlag = false;

        if ((tokenToCompareLeft = dynamic_cast<Identifier*>(arithOpPtr->getIdentifierArithOpPtrValue())) != nullptr &&
            (tokenToCompareRight = dynamic_cast<Identifier*>(arithOpPtr->getIdentifierArithOp_PtrValue())) != nullptr
           )
        {
            this->climbTreeToDeclarationAndVerifyArithmeticOperationsAreCorrectlyDefined(tokenToCompareLeft, tokenToCompareRight, leftTokInserted,
                                                                                         rightTokInserted, expressionPresentFlag);
        }

        else if ((tokenToCompareLeft = dynamic_cast<Number*>(arithOpPtr->getNumberArithOpPtrValue())) != nullptr ||
                 (tokenToCompareRight = dynamic_cast<Number*>(arithOpPtr->getNumberArithOp_PtrValue())) != nullptr
                )
        {
            if ((tokenToCompareLeft = dynamic_cast<Identifier*>(arithOpPtr->getNumberArithOpPtrValue())) != nullptr)
            {
                tokenToCompareRight = dynamic_cast<Number*>(arithOpPtr->getNumberArithOp_PtrValue());
            }

            else if ((tokenToCompareRight = dynamic_cast<Identifier*>(arithOpPtr->getNumberArithOp_PtrValue())) != nullptr)
            {
                tokenToCompareLeft = dynamic_cast<Number*>(arithOpPtr->getNumberArithOpPtrValue());
            }

            
            this->climbTreeToDeclarationAndVerifyArithmeticOperationsAreCorrectlyDefined(tokenToCompareLeft, tokenToCompareRight, leftTokInserted,
                rightTokInserted, expressionPresentFlag);
        }
    }

    else if (dynamic_cast<ArithOp_*>(this) != nullptr)
    {
        //Identifier will set its ArithOpPtr to arithOpPtr.
        ArithOp* arithOpPtr = nullptr;
        if ((arithOpPtr = dynamic_cast<ArithOp*>(this->parentNodePtr)) != nullptr)
        {
            if (dynamic_cast<Number*>(tokenToCompare) != nullptr)
            {
                arithOpPtr->setNumberArithOp_PtrValue(tokenToCompare);
                numberSet = true;
            }
           
            else if(dynamic_cast<Identifier*>(tokenToCompare) != nullptr)
            {
                arithOpPtr->setIdentifierArithOp_PtrValue(tokenToCompare);
            }
            
        }
   
    }

    this->parentNodePtr->climbTreeAndVerifyArithmeticOperationsAreCorrectlyDefined(tokenToCompare, numberSet);
    
}

void ParseTreeNode::climbTreeAndVerifyTermOperationsAreCorrectlyDefined(ParseTreeNode* tokenToCompare, bool numberSet)
{
    //Identifier and Number will call this method.
    //Then ArithOp_ will call this method.
    Term_* term_Ptr = nullptr;
    Term* termPtr = nullptr;
    Declaration* declPtr = nullptr;
    Identifier* identifierArithOpPtr = nullptr;
    Identifier* identifierArithOp_Ptr = nullptr;



    if (this->parentNodePtr == nullptr)
    {
        return;
    }
    else if ((termPtr = dynamic_cast<Term*>(this)) != nullptr)
    {
        //Identifier will set its ArithOpPtr to arithOpPtr.
        if (dynamic_cast<Number*>(tokenToCompare) != nullptr && !numberSet)
        {
            termPtr->setNumberTermPtrValue(tokenToCompare);
        }
        else if (dynamic_cast<Identifier*>(tokenToCompare) != nullptr)
        {
            termPtr->setIdentifierTermPtrValue(tokenToCompare);
        }

        //If both ArithOp ptr values are not equal to nullptr, we will continue to climb the tree to declaration.
        //When we get there, we will do the type checking portion.
        //We have to pass both pointers up to <Declaration>, search <Declaration> for the respective Identifier
        //and then do the check.  
        //We will start this either late tomorrow or on Monday, since I have another project to work on tomorrow after 
        //I am finally able to go to church with mask, since I received my first dose of the COVID-19 Pfizer vaccine!
        //I still wear a KN-95 mask though, until the week following my second dose.  Then I will downgrade to a cloth mask.

        ParseTreeNode* tokenToCompareLeft = nullptr;
        ParseTreeNode* tokenToCompareRight = nullptr;
        bool leftTokInserted = false;
        bool rightTokInserted = false;
        bool expressionPresentFlag = false;

        if ((tokenToCompareLeft = dynamic_cast<Identifier*>(termPtr->getIdentifierTermPtrValue())) != nullptr &&
            (tokenToCompareRight = dynamic_cast<Identifier*>(termPtr->getIdentifierTerm_PtrValue())) != nullptr
            )
        {
            this->climbTreeToDeclarationAndVerifyArithmeticOperationsAreCorrectlyDefined(tokenToCompareLeft, tokenToCompareRight, leftTokInserted,
                rightTokInserted, expressionPresentFlag);
        }

        else if ((tokenToCompareLeft = dynamic_cast<Number*>(termPtr->getNumberTermPtrValue())) != nullptr ||
            (tokenToCompareRight = dynamic_cast<Number*>(termPtr->getNumberTerm_PtrValue())) != nullptr
            )
        {
            if ((tokenToCompareLeft = dynamic_cast<Identifier*>(termPtr->getNumberTermPtrValue())) != nullptr)
            {
                tokenToCompareRight = dynamic_cast<Number*>(termPtr->getNumberTerm_PtrValue());
            }

            else if ((tokenToCompareRight = dynamic_cast<Identifier*>(termPtr->getNumberTerm_PtrValue())) != nullptr)
            {
                tokenToCompareLeft = dynamic_cast<Number*>(termPtr->getNumberTerm_PtrValue());
            }


            this->climbTreeToDeclarationAndVerifyArithmeticOperationsAreCorrectlyDefined(tokenToCompareLeft, tokenToCompareRight, leftTokInserted,
                rightTokInserted, expressionPresentFlag);
        }
    }

    else if (dynamic_cast<Term_*>(this) != nullptr)
    {
        //Identifier will set its ArithOpPtr to arithOpPtr.
        Term* termPtr = nullptr;
        if ((termPtr = dynamic_cast<Term*>(this->parentNodePtr)) != nullptr)
        {
            if (dynamic_cast<Number*>(tokenToCompare) != nullptr)
            {
                termPtr->setNumberTerm_PtrValue(tokenToCompare);
                numberSet = true;
            }

            else if (dynamic_cast<Identifier*>(tokenToCompare) != nullptr)
            {
                termPtr->setIdentifierTerm_PtrValue(tokenToCompare);
            }

        }




    }

    this->parentNodePtr->climbTreeAndVerifyTermOperationsAreCorrectlyDefined(tokenToCompare, numberSet);

}

#define OUT 0
#ifndef OUT
void ParseTreeNode::climbTreeToNearestExpressionAndSetParenthesesFlag()
{
    TerminalNode* term = nullptr;
    Expression* expr = nullptr;
    if ((expr = dynamic_cast<Expression*>(this)) != nullptr)
    {
        if ((term = dynamic_cast<TerminalNode*>(expr->getLinkedMemberNonterminalsList().at(0))) != nullptr &&
             term->getNodeTokenValue() == "not")
        {
            term->setParenthesesPresentFlag(true);
        }
        
        return;
    }

    else if (this->parentNodePtr == nullptr)
    {
        return;
    }

    parentNodePtr->climbTreeToNearestExpressionAndSetParenthesesFlag();
}

#endif

void ParseTreeNode::climbTreeAndVerifyExpressionOperationsAreCorrectlyDefined(ParseTreeNode* tokenToCompare, bool numberSet,
                                                                              bool &expressionPresentFlag
                                                                             )
{
    //Identifier and Number will call this method.
    //Then ArithOp_ will call this method.
    Expression_* expression_Ptr = nullptr;
    Expression* expressionPtr = nullptr;
    Declaration* declPtr = nullptr;
    Identifier* identifierArithOpPtr = nullptr;
    Identifier* identifierArithOp_Ptr = nullptr;



    if (this->parentNodePtr == nullptr)
    {
        return;
    }
    else if ((expressionPtr = dynamic_cast<Expression*>(this)) != nullptr)
    {
        //Identifier will set its ArithOpPtr to arithOpPtr.
        TerminalNode* term = nullptr;
        if (!expressionPtr->getLinkedMemberNonterminalsList().empty() &&
            (term = dynamic_cast<TerminalNode*>(expressionPtr->getLinkedMemberNonterminalsList().at(0))) != nullptr

            )
        {
            if (term->getNodeTokenValue() == "not")
            {
                //cout << "\nNot Found.";

                //Figure out what to do about this later.  TODO!!
                Number* num = nullptr;
                Identifier* ident = nullptr;
                if ((num = dynamic_cast<Number*>(tokenToCompare)) != nullptr && !numberSet)
                {
                    expressionPtr->setNumberExpressionPtrValue(tokenToCompare);

                    //We need this because this will be hit for each value in expression and we
                    //don't want it to set the not flag for every identifier that is hit, if it is not preceded by "not"
                    if (term->getNodeTokenValue() == "not")
                    {
                        if (!expressionPresentFlag)
                        {
                            num->setConvertToNotValue(true);

                        }

                        else if ((ident = dynamic_cast<Identifier*>(tokenToCompare)) != nullptr)
                        {
                            expressionPtr->setIdentifierExpressionPtrValue(tokenToCompare);

                            if (!expressionPresentFlag)
                            {
                                ident->setConvertToNotValue(true);
                            }
                        }
                    }
                }
            }
        }


        else if (dynamic_cast<Number*>(tokenToCompare) != nullptr && !numberSet)
        {
            expressionPtr->setNumberExpressionPtrValue(tokenToCompare);
            numberSet = true;



        }
        else if (dynamic_cast<Identifier*>(tokenToCompare) != nullptr && !numberSet)
        {
            expressionPtr->setIdentifierExpressionPtrValue(tokenToCompare);
        }




        //If both ArithOp ptr values are not equal to nullptr, we will continue to climb the tree to declaration.
        //When we get there, we will do the type checking portion.
        //We have to pass both pointers up to <Declaration>, search <Declaration> for the respective Identifier
        //and then do the check.  
        //We will start this either late tomorrow or on Monday, since I have another project to work on tomorrow after 
        //I am finally able to go to church with mask, since I received my first dose of the COVID-19 Pfizer vaccine!
        //I still wear a KN-95 mask though, until the week following my second dose.  Then I will downgrade to a cloth mask.

        ParseTreeNode* tokenToCompareLeft = nullptr;
        ParseTreeNode* tokenToCompareRight = nullptr;
        bool leftTokInserted = false;
        bool rightTokInserted = false;


        if ((tokenToCompareLeft = dynamic_cast<Identifier*>(expressionPtr->getIdentifierExpressionPtrValue())) != nullptr &&
            (tokenToCompareRight = dynamic_cast<Identifier*>(expressionPtr->getIdentifierExpression_PtrValue())) != nullptr
            )
        {


            this->climbTreeToDeclarationAndVerifyArithmeticOperationsAreCorrectlyDefined(tokenToCompareLeft, tokenToCompareRight, leftTokInserted,
                rightTokInserted, expressionPresentFlag);
        }

        else if ((tokenToCompareLeft = dynamic_cast<Number*>(expressionPtr->getNumberExpressionPtrValue())) != nullptr ||
            (tokenToCompareRight = dynamic_cast<Number*>(expressionPtr->getNumberExpression_PtrValue())) != nullptr
            )
        {


            if ((tokenToCompareLeft = dynamic_cast<Identifier*>(expressionPtr->getNumberExpressionPtrValue())) != nullptr)
            {
                tokenToCompareRight = dynamic_cast<Number*>(expressionPtr->getNumberExpression_PtrValue());
            }

            else if ((tokenToCompareRight = dynamic_cast<Identifier*>(expressionPtr->getNumberExpression_PtrValue())) != nullptr)
            {
                tokenToCompareLeft = dynamic_cast<Number*>(expressionPtr->getNumberExpressionPtrValue());
            }

            this->climbTreeToDeclarationAndVerifyArithmeticOperationsAreCorrectlyDefined(tokenToCompareLeft, tokenToCompareRight, leftTokInserted,
                rightTokInserted, expressionPresentFlag);
        }
    }
    

    else if (dynamic_cast<Expression_*>(this) != nullptr)
    {
        //Identifier will set its ArithOpPtr to arithOpPtr.
        Expression* expressionPtr = nullptr;
        if ((expressionPtr = dynamic_cast<Expression*>(this->parentNodePtr)) != nullptr)
        {
            TerminalNode* term = nullptr;
            Number* num = nullptr;
            Identifier* ident = nullptr;

            if ((term = dynamic_cast<TerminalNode*>(this->getLinkedMemberNonterminalsList().at(0)))->getNodeTokenValue() == "&" ||
                (term = dynamic_cast<TerminalNode*>(this->getLinkedMemberNonterminalsList().at(0)))->getNodeTokenValue() == "|"
                )
            {
                expressionPresentFlag = true;
                
            }

            if ((num = dynamic_cast<Number*>(tokenToCompare)) != nullptr)
            {
                expressionPtr->setNumberExpression_PtrValue(tokenToCompare);
                numberSet = true;
                if (num->getConvertToNotValue())
                {
                    num->setNodeTokenIntegerDoubleNumberTokenValueToNotValue();
                }
            }

            else if ((ident = dynamic_cast<Identifier*>(tokenToCompare)) != nullptr)
            {
                expressionPtr->setIdentifierExpression_PtrValue(tokenToCompare);
               
            }

          

        }

    }

    this->parentNodePtr->climbTreeAndVerifyExpressionOperationsAreCorrectlyDefined(tokenToCompare, numberSet, expressionPresentFlag);

}


void ParseTreeNode::verifyArithmeticOperationsAreCorrectlyDefinedDigAndBurnClockCycles(ParseTreeNode* tokenToCompareLeft, ParseTreeNode* tokenToCompareRight,
                                                                                       std::string &leftValue, std::string &rightValue, bool &numberSet)
{
    
    //Here, we dig until we can find a <VariableDeclaration> class.
    if (this->linkedMemberNonterminals.empty())
    {
        //We have reached a leaf, so we need to return.  Prevents infinite recursion.
        return;
    }
    

    else
    {
        

        for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
        {
            VariableDeclaration* varDecl = nullptr;


            if ((varDecl = dynamic_cast<VariableDeclaration*>(this->linkedMemberNonterminals.at(i))) != nullptr)
            {
                //We check for the identifier.
                //Otherwise, we dig, arrive here or a leaf, and repeat again.
                //If we arrive at a leaf and don't find anything, we jump back to <Declaration>, climb the tree to the
                //<Program> class, then dig again. 
                //Then, if we really don't come up lucky, we are basically screwed.  We should have already thrown a 
                //Variable not defined exception, but only time will tell whether this occurred before this check was completed and
                //tested .  We could throw more exceptions, though, just to make the user's life more miserable and stab him/her a 
                //few more times.

                //cout << "\nWe have arrived at a DECLARATION!  Digging was successful!";

                //Jesus!  Now, we can actually check to determine whether the <Identifier>s match and the <TypeMark>s match.
                Identifier* ident = nullptr;
                TypeMark* identType = nullptr;
                


                if ((ident = dynamic_cast<Identifier*>(varDecl->linkedMemberNonterminals.at(1))) != nullptr &&
                    ((identType = dynamic_cast<TypeMark*>(varDecl->linkedMemberNonterminals.at(3))) != nullptr)
                    )
                {
                    //We check their types.
                    string symbolTableTest;

                    if ((symbolTableTest = dynamic_cast<TerminalNode*>(identType->getLinkedMemberNonterminalsList().at(0))->getNodeTokenValue()) == "integer" ||
                        (symbolTableTest = dynamic_cast<TerminalNode*>(identType->getLinkedMemberNonterminalsList().at(0))->getNodeTokenValue()) == "float"
                        )
                    {
                        Number* numberLeft = nullptr;
                        Number* numberRight = nullptr;

                        if (!numberSet && ((numberLeft = dynamic_cast<Number*>(tokenToCompareLeft)) != nullptr ||
                            (numberRight = dynamic_cast<Number*>(tokenToCompareRight)) != nullptr)
                            )
                        {
                            if (numberLeft != nullptr)
                            {
                                leftValue = numberLeft->getNumberTokenType();
                                numberSet = true;

                            }

                            else if (numberRight != nullptr)
                            {
                                rightValue = numberRight->getNumberTokenType();
                                numberSet = true;

                            }

                        }
                        
                        //We can set either the right hand or left-hand values.
                        else if (dynamic_cast<Number*>(tokenToCompareLeft) == nullptr && 
                                 ident->getNodeTokenValue() == dynamic_cast<Identifier*>(tokenToCompareLeft)->getNodeTokenValue()
                                )
                        {
                            leftValue = ident->getNodeTokenValue().c_str();
                        }

                        else if (dynamic_cast<Number*>(tokenToCompareRight) == nullptr && 
                                 ident->getNodeTokenValue() == dynamic_cast<Identifier*>(tokenToCompareRight)->getNodeTokenValue()
                                )
                        {
                            rightValue = ident->getNodeTokenValue().c_str();
                        }


                    }

                    //Now, we check the values somewhere along the line and then decide what to do.  TODO!
                }

                //And in all of this fun, I forgot to recurse.  This should be really fun.  Multiple recursion!  We should
                //make it more confusing and put each recursive method on its own thread.
            }
                this->linkedMemberNonterminals.at(i)->verifyArithmeticOperationsAreCorrectlyDefinedDigAndBurnClockCycles(tokenToCompareLeft, tokenToCompareRight,
                    leftValue, rightValue, numberSet);  
        }
    }
   
}

void ParseTreeNode::verifyExpressionOperationsAreCorrectlyDefinedDigAndBurnClockCycles(ParseTreeNode* tokenToCompareLeft, ParseTreeNode* tokenToCompareRight,
    std::string& leftValue, std::string& rightValue, bool& numberSet)
{

    //Here, we dig until we can find a <VariableDeclaration> class.
    if (this->linkedMemberNonterminals.empty())
    {
        //We have reached a leaf, so we need to return.  Prevents infinite recursion.
        return;
    }


    else
    {


        for (int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
        {
            VariableDeclaration* varDecl = nullptr;


            if ((varDecl = dynamic_cast<VariableDeclaration*>(this->linkedMemberNonterminals.at(i))) != nullptr)
            {
                //We check for the identifier.
                //Otherwise, we dig, arrive here or a leaf, and repeat again.
                //If we arrive at a leaf and don't find anything, we jump back to <Declaration>, climb the tree to the
                //<Program> class, then dig again. 
                //Then, if we really don't come up lucky, we are basically screwed.  We should have already thrown a 
                //Variable not defined exception, but only time will tell whether this occurred before this check was completed and
                //tested .  We could throw more exceptions, though, just to make the user's life more miserable and stab him/her a 
                //few more times.

                //cout << "\nWe have arrived at a DECLARATION!  Digging was successful!";

                //Jesus!  Now, we can actually check to determine whether the <Identifier>s match and the <TypeMark>s match.
                Identifier* ident = nullptr;
                TypeMark* identType = nullptr;

                Number* numberLeft = nullptr;
                Number* numberRight = nullptr;

                if (!numberSet && ((numberLeft = dynamic_cast<Number*>(tokenToCompareLeft)) != nullptr ||
                    (numberRight = dynamic_cast<Number*>(tokenToCompareRight)) != nullptr)
                    )
                {
                    //We can't use else-if if both numberLeft and numberRight happen to be defined.  
                    //Then, only one will be set to its boolean equivalent.

                    if (numberLeft != nullptr)
                    {
                        leftValue = numberLeft->getNumberTokenType();
                        if (leftValue == "INTEGER_LITERAL")
                        {
                            numberLeft->setNodeTokenIntegerDoubleNumberTokenValueToBoolean();
                        }

                        else if(leftValue == "FLOATING_POINT_LITERAL")
                        {
                            //throw the exception.  It must be a FLOATING_POINT_LITERAL.
                            throw ExpressionOperatorsAreNotAValidTypeException();
                        }
                        
                        numberSet = true;

                    }

                    if (numberRight != nullptr)
                    {
                        rightValue = numberRight->getNumberTokenType();
                        if (rightValue == "INTEGER_LITERAL")
                        {
                            numberRight->setNodeTokenIntegerDoubleNumberTokenValueToBoolean();
                        }

                        else if (leftValue == "FLOATING_POINT_LITERAL")
                        {
                            //throw the exception.  It must be a FLOATING_POINT_LITERAL.
                            throw ExpressionOperatorsAreNotAValidTypeException();
                        }
                        numberSet = true;

                    }

                }



                else if ((ident = dynamic_cast<Identifier*>(varDecl->linkedMemberNonterminals.at(1))) != nullptr &&
                    ((identType = dynamic_cast<TypeMark*>(varDecl->linkedMemberNonterminals.at(3))) != nullptr)
                    )
                {
                    //We check their types.
                    string symbolTableTest;



                    if ((symbolTableTest = dynamic_cast<TerminalNode*>(identType->getLinkedMemberNonterminalsList().at(0))->getNodeTokenValue()) == "integer" ||
                        (symbolTableTest = dynamic_cast<TerminalNode*>(identType->getLinkedMemberNonterminalsList().at(0))->getNodeTokenValue()) == "bool"
                        )
                    {
                        

                        if (!numberSet && ((numberLeft = dynamic_cast<Number*>(tokenToCompareLeft)) != nullptr ||
                            (numberRight = dynamic_cast<Number*>(tokenToCompareRight)) != nullptr)
                            )
                        {
                            if (numberLeft != nullptr)
                            {
                                leftValue = numberLeft->getNumberTokenType();
                                numberSet = true;

                            }

                            else if (numberRight != nullptr)
                            {
                                rightValue = numberRight->getNumberTokenType();
                                numberSet = true;

                            }

                        }

                        //We can set either the right hand or left-hand values.
                        else if (dynamic_cast<Number*>(tokenToCompareLeft) == nullptr &&
                            ident->getNodeTokenValue() == dynamic_cast<Identifier*>(tokenToCompareLeft)->getNodeTokenValue()
                            )
                        {
                            leftValue = ident->getNodeTokenValue().c_str();
                            if (symbolTableTest == "integer")
                            {
                                //We have to convert that identifier to a booleanValue
                                cout << "\nIdentifier is integer.";
                                //We need to tag the Identifier as a "convert to boolean result", so it can
                                //Automatically occur during intermediate-code generation.  We can't really
                                //do the conversion until we actually write the IR code for the Expression.  
                                //However, we can signal our compiler to do this when it gets to this point,
                                //by setting a flag on that Identifier/Number within this method.

                                dynamic_cast<Identifier*>(tokenToCompareLeft)->setreadIntegerAsBooleanValueFlagValue(true);

                            }
                        }

                        else if (dynamic_cast<Number*>(tokenToCompareRight) == nullptr &&
                            ident->getNodeTokenValue() == dynamic_cast<Identifier*>(tokenToCompareRight)->getNodeTokenValue()
                            )
                        {
                            rightValue = ident->getNodeTokenValue().c_str();

                            if (symbolTableTest == "integer")
                            {
                                //We have to convert that identifier to a booleanValue
                                //cout << "\nIdentifier is integer.";

                                dynamic_cast<Identifier*>(tokenToCompareRight)->setreadIntegerAsBooleanValueFlagValue(true);
                            }
                            
                        }

                        

                    }

                    //Now, we check the values somewhere along the line and then decide what to do.  TODO!
                }

                //And in all of this fun, I forgot to recurse.  This should be really fun.  Multiple recursion!  We should
                //make it more confusing and put each recursive method on its own thread.
            }
            this->linkedMemberNonterminals.at(i)->verifyExpressionOperationsAreCorrectlyDefinedDigAndBurnClockCycles(tokenToCompareLeft, tokenToCompareRight,
                leftValue, rightValue, numberSet);
        }
    }

}
void ParseTreeNode::climbTreeToDeclarationAndVerifyArithmeticOperationsAreCorrectlyDefined(ParseTreeNode* tokenToCompareLeft,
                                                                                           ParseTreeNode* tokenToCompareRight,
                                                                                           bool &leftTokInserted, bool &rightTokInserted,
                                                                                           bool &expressionPresentFlag
                                                                                          )
{
    Identifier* identifierArithOpPtr = nullptr;
    Identifier* identifierArithOp_Ptr = nullptr;
    Program* prog;
    Declaration* decl;
   
    
    
    if (tokenToCompareLeft == nullptr && tokenToCompareRight == nullptr)
    {
        return;
    }

    else if ((prog = dynamic_cast<Program*>(this)) != nullptr)
    {
        

        if ((identifierArithOpPtr = dynamic_cast<Identifier*>(tokenToCompareLeft)) != nullptr &&
            (identifierArithOpPtr = dynamic_cast<Identifier*>(tokenToCompareRight)) != nullptr
            )
        {
            prog->verifyArithmeticOperationsAreCorrectlyDefined(dynamic_cast<Identifier*>(tokenToCompareLeft),
                                                                dynamic_cast<Identifier*>(tokenToCompareRight),
                                                                leftTokInserted, rightTokInserted);
            if (expressionPresentFlag)
            {
                dynamic_cast<Identifier*>(tokenToCompareLeft)->setBitwiseAndOrOperationDefinedFlagValue(true);
                dynamic_cast<Identifier*>(tokenToCompareRight)->setBitwiseAndOrOperationDefinedFlagValue(true);
            }
            return;
        }

        else if (dynamic_cast<Number*>(tokenToCompareLeft) != nullptr || dynamic_cast<Number*>(tokenToCompareRight) != nullptr)
        {
            if (dynamic_cast<Number*>(tokenToCompareLeft) != nullptr)
            {
                prog->verifyArithmeticOperationsAreCorrectlyDefinedNumberLeft(dynamic_cast<Number*>(tokenToCompareLeft),
                                                                              dynamic_cast<Identifier*>(tokenToCompareRight),
                                                                              leftTokInserted, rightTokInserted);
                if (expressionPresentFlag)
                {
                    
                    dynamic_cast<Identifier*>(tokenToCompareRight)->setBitwiseAndOrOperationDefinedFlagValue(true);
                    dynamic_cast<Number*>(tokenToCompareLeft)->setBitwiseAndOrOperationDefinedFlagValue(true);
                   
                }
                return;
            }

            else if (dynamic_cast<Number*>(tokenToCompareRight) != nullptr)
            {
                prog->verifyArithmeticOperationsAreCorrectlyDefinedNumberRight(dynamic_cast<Identifier*>(tokenToCompareLeft),
                                                                               dynamic_cast<Number*>(tokenToCompareRight),
                                                                               leftTokInserted, rightTokInserted);
                if (expressionPresentFlag)
                {

                    dynamic_cast<Identifier*>(tokenToCompareLeft)->setBitwiseAndOrOperationDefinedFlagValue(true);
                    dynamic_cast<Number*>(tokenToCompareRight)->setBitwiseAndOrOperationDefinedFlagValue(true);
                }
                return;
            }
        }
    }

    else if ((decl = dynamic_cast<Declaration*>(this)) != nullptr)
    {
        

        if ((identifierArithOpPtr = dynamic_cast<Identifier*>(tokenToCompareLeft)) != nullptr &&
            (identifierArithOpPtr = dynamic_cast<Identifier*>(tokenToCompareRight)) != nullptr
            )
        {
            
            
            decl->verifyArithmeticOperationsAreCorrectlyDefined(dynamic_cast<Identifier*>(tokenToCompareLeft),
                                                                dynamic_cast<Identifier*>(tokenToCompareRight), 
                                                                leftTokInserted, rightTokInserted);
            if (expressionPresentFlag)
            {
                dynamic_cast<Identifier*>(tokenToCompareLeft)->setBitwiseAndOrOperationDefinedFlagValue(true);
                dynamic_cast<Identifier*>(tokenToCompareRight)->setBitwiseAndOrOperationDefinedFlagValue(true);
            }
            set<pair<ParseTreeNode*, ParseTreeNode*>>::iterator it = this->tokenToCompare.begin();
           
            
            
            //We don't want to return.  We want to visit every declaration up until we visit the global symbol table, and
            //add what we have to every set.
        }

        else if (dynamic_cast<Number*>(tokenToCompareLeft) != nullptr || dynamic_cast<Number*>(tokenToCompareRight) != nullptr)
        {
            if (dynamic_cast<Number*>(tokenToCompareLeft) != nullptr)
            {
                decl->verifyArithmeticOperationsAreCorrectlyDefinedNumberLeft(dynamic_cast<Number*>(tokenToCompareLeft),
                    dynamic_cast<Identifier*>(tokenToCompareRight),
                    leftTokInserted, rightTokInserted);

                if (expressionPresentFlag)
                {
                    
                    dynamic_cast<Identifier*>(tokenToCompareRight)->setBitwiseAndOrOperationDefinedFlagValue(true);
                    dynamic_cast<Number*>(tokenToCompareLeft)->setBitwiseAndOrOperationDefinedFlagValue(true);
                }
                //We don't return here.
            }

            else if (dynamic_cast<Number*>(tokenToCompareRight) != nullptr)
            {
                decl->verifyArithmeticOperationsAreCorrectlyDefinedNumberRight(dynamic_cast<Identifier*>(tokenToCompareLeft),
                    dynamic_cast<Number*>(tokenToCompareRight),
                    leftTokInserted, rightTokInserted);

                if (expressionPresentFlag)
                {

                    dynamic_cast<Identifier*>(tokenToCompareLeft)->setBitwiseAndOrOperationDefinedFlagValue(true);
                    dynamic_cast<Number*>(tokenToCompareRight)->setBitwiseAndOrOperationDefinedFlagValue(true);
                }
                //We don't return here.
            }
        }
    }

    this->parentNodePtr->climbTreeToDeclarationAndVerifyArithmeticOperationsAreCorrectlyDefined(tokenToCompareLeft, tokenToCompareRight,
                                                                                                leftTokInserted, rightTokInserted, expressionPresentFlag);
}

void ParseTreeNode::climbTreeAndVerifyArrayIndices(ParseTreeNode* numberNode)
{
    try
    {
        Destination* dest = nullptr;
        Name* name = nullptr;
        VariableDeclaration* varDecl = nullptr;

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
                    //Now, climb the tree until we reach a <Declaration>.  Pass this pointer to that method.
                    //However, you had better first pick up the <Identifier> and pass it up to <Declaration> so we know which variable
                    //to look at for the bounds check.
                    Identifier* identifierNode = dynamic_cast<Identifier*>(this->getLinkedMemberNonterminalsList().at(0));
                    this->climbTreeToDeclarationNode(identifierNode);
                }
            }
        } 
        else if ((name = dynamic_cast<Name*>(this)) != nullptr)
        {
            //We are currently at <Destination*> non-terminal, and we have to check to see if we have an expression.
            //We search the non-terminals.
            vector<ParseTreeNode*> resultList = name->getLinkedMemberNonterminalsList();
            for (int i = 0; i < resultList.size(); ++i)
            {
                TerminalNode* termNode = nullptr;
                if ((termNode = dynamic_cast<TerminalNode*>(resultList.at(i))) != nullptr && termNode->getNodeTokenValue() == "[")
                {
                   name->checkArrayIndexIsIntegerLiteral(numberNode);
                    //Now, climb the tree until we reach a <Declaration>.  Pass this pointer to that method.
                    //However, you had better first pick up the <Identifier> and pass it up to <Declaration> so we know which variable
                    //to look at for the bounds check.
                    Identifier* identifierNode = dynamic_cast<Identifier*>(this->getLinkedMemberNonterminalsList().at(0));
                    this->climbTreeToDeclarationNode(identifierNode);
                }
            }
        }

        else if ((varDecl = dynamic_cast<VariableDeclaration*>(this)) != nullptr)
        {
            //We are currently at <Destination*> non-terminal, and we have to check to see if we have an expression.
            //We search the non-terminals.
            vector<ParseTreeNode*> resultList = varDecl->getLinkedMemberNonterminalsList();
            for (int i = 0; i < resultList.size(); ++i)
            {
                TerminalNode* termNode = nullptr;
                if ((termNode = dynamic_cast<TerminalNode*>(resultList.at(i))) != nullptr && termNode->getNodeTokenValue() == "[")
                {
                    varDecl->checkArrayIndexIsIntegerLiteral(numberNode);
                }
            }
        }
    }
    catch (ArrayIndexNotAnIntegerLiteralException& e)
    {
        cout << endl << endl << e.what() << dynamic_cast<Number*>(numberNode)->getNodeTokenLineNumber();
        return;
    }
    //recurse
    this->parentNodePtr->climbTreeAndVerifyArrayIndices(numberNode);
}

vector<ParseTreeNode*>& ParseTreeNode::getLinkedMemberNonterminalsList()
{
    return this->linkedMemberNonterminals;
}

void ParseTreeNode::climbTreeToDeclarationNode(ParseTreeNode* identifierNode)
{
    if (this->parentNodePtr == nullptr)
    {
        if (dynamic_cast<Program*>(this))
        {
            //Now, perform the array bounds check.
            //We search the global symbol table here.
            for (int s = 0; s < this->getSymbolTable()->size(); ++s)
            {
                Identifier* symbolTableIdent = nullptr;

                if ((symbolTableIdent = dynamic_cast<Identifier*>(this->getSymbolTable()->at(s))) != nullptr &&
                    symbolTableIdent->getNodeTokenValue() == dynamic_cast<Identifier*>(identifierNode)->getNodeTokenValue()
                    )
                {
                    this->checkArrayIndexInBounds(*identifierNode, *symbolTableIdent);
                }
            }
        }
        return;
    }
    else if (dynamic_cast<Declaration*>(this))
    {
        //Now, perform the array bounds check.
        //Search the symbol table
        for (int s = 0; s < this->getSymbolTable()->size(); ++s)
        {
            Identifier* symbolTableIdent = nullptr;

            if ((symbolTableIdent = dynamic_cast<Identifier*>(this->getSymbolTable()->at(s))) != nullptr &&
                 symbolTableIdent->getNodeTokenValue() == dynamic_cast<Identifier*>(identifierNode)->getNodeTokenValue()
               )
            {
                this->checkArrayIndexInBounds(*identifierNode, *symbolTableIdent);
            }
        }
    }

    
    this->parentNodePtr->climbTreeToDeclarationNode(identifierNode);
}

void ParseTreeNode::checkArrayIndexInBounds(ParseTreeNode& identifier, ParseTreeNode& symbolTableIdentifier)
{
    Number* indexToCheck = nullptr;
    try
    {
        if ((indexToCheck = dynamic_cast<Number*>(dynamic_cast<Identifier*>(&identifier)->getNumberPtrValue())) != nullptr)
        {
            if (!(indexToCheck->getNodeTokenIntegerDoubleNumberTokenValue() >= 0 &&
                  indexToCheck->getNodeTokenIntegerDoubleNumberTokenValue() <=
                  dynamic_cast<Number*>(dynamic_cast<Identifier*>(&symbolTableIdentifier)->getNumberPtrValue())->getNodeTokenIntegerDoubleNumberTokenValue()
                )
                )
            {
                //Throw the exception.  Array Index is out of bounds.
                throw ArrayIndexOutOfBoundsException();
            }
        }
    }
    catch (ArrayIndexOutOfBoundsException& e)
    {
        cout << endl << endl << e.what() << dynamic_cast<Identifier*>(&identifier)->getNodeTokenLineNumber()
            << " Identifier Name: "      << dynamic_cast<Identifier*>(&identifier)->getNodeTokenValue()
            << " Current Bound Value: "  << dynamic_cast<Number*>(dynamic_cast<Identifier*>(&identifier)->getNumberPtrValue())->getNodeTokenIntegerDoubleNumberTokenValue()
            << " Declared Bound Value: "
            << dynamic_cast<Number*>(dynamic_cast<Identifier*>(&symbolTableIdentifier)->getNumberPtrValue())->getNodeTokenIntegerDoubleNumberTokenValue()
            << endl;
    }
}