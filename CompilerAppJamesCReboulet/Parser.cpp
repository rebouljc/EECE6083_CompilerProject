#include "Parser.h"


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
}

Parser::~Parser()
{
    this->cleanUp();
    for (int i = 0; i < this->storedTokens.size(); ++i)
    {
        delete (this->storedTokens.at(i));
    }
   
}

void Parser::parseTokensLoop(Token* tok)
{

}