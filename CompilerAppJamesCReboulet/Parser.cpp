#include "Parser.h"
#include "Program.h"


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
void Parser::parseTokensLoop()
{
    //create the parse tree
    ParseTreeNode* parseTree = new Program(this); //This is the first node of the linked list.  I will create a class for each of the non-terminals in the grammar.
    //Now program will contain its terminal tokens and non-terminal classes which all inherit from ParseTreeNode* abstract class.

}