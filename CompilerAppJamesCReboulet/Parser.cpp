#include "Parser.h"
#include "Program.h"
#include "TerminalNode.h"
#include "IntermediateCodeGenerator.h"



Parser::Parser()
{
    try
    {
       this->init();
    }

    catch (StringLiteralException& e)
    {
        cout << endl << e.what() << this->getLineNumber();
    }

    catch (IdentifierBeginsWithNumberException& e)
    {
        cout << endl << e.what() << this->getLineNumber();
    }

    catch (NoClosingCommentMarkException& e)
    {
        cout << endl << e.what() << this->getFirstCommentLineNumber();
    }

    catch (IllegalEqualsSignException& e)
    {
        cout << endl << e.what() << this->getLineNumber();
    }

    catch (IllegalIdentifierException& e)
    {
        cout << endl << e.what() << this->getLineNumber();
    }

   
     this->parseTokensLoop();
    

}

Parser::~Parser()
{
    
    this->cleanUp();
    
    for (int i = 0; i < this->storedTokens.size(); ++i)
    {
        delete (this->storedTokens.at(i));
    }
   
}
vector<Token*>* Parser::getStoredTokensList()
{
    return &this->storedTokens;
}

Token* Parser::readNextToken()
{
    Token* tokToReturn;
    if (this->indexToRead < this->getStoredTokensList()->size())
    {
        tokToReturn = this->getStoredTokensList()->at(this->indexToRead);
        ++ this->indexToRead;
    }

    else
    {
        tokToReturn = nullptr;
    }

    return tokToReturn;


}
void Parser::parseTokensLoop()
{
    //create the parse tree
    ParseTreeNode* parseTree = new Program(this); //This is the first node of the linked list.  I will create a class for each of the non-terminals in the grammar.
    //Now program will contain its terminal tokens and non-terminal classes which all inherit from ParseTreeNode* abstract class.
    //If I want to now search the entire tree, I will create a separate pointer and cast the Program Pointer to a parseTree. 
    //create a virtual search method in each class and return a pointer to that object when the 
                                          //search method is called.  
    

    vector<ParseTreeNode*>* searchResultsList = parseTree->getSearchResultsList(parseTree);
    //Currently, search is a depth-first search of the parseTree.  Put this in intermediate code generator.   

    //Call the intermediate code generator from here.  This is all we can do, since we can't store the linked list globally. 
    //We need this dependency, unfortunately or we risk violating the encapsulation principle of OOP.  
    
    IntermediateCodeGenerator* intermediate = new IntermediateCodeGenerator(parseTree);
    
    //Now, we have to clean up the memory to fix memory leaks.
    for (int i = 0; i < searchResultsList->size(); ++i)
    {
        delete(searchResultsList->at(i));
       
    }

    
    delete (intermediate);
    
}


    