// CompilerAppJamesCReboulet.cpp


#include <iostream>
#include "Token.h"
#include "Scanner.h"
#include "StringLiteralException.h"
#include "IdentifierBeginsWithNumberException.h"
#include "NoClosingCommentMarkException.h"

Scanner* scan = new Scanner();

int main()
{
    
    try
    {
        scan->init();
    }

    catch (StringLiteralException& e)
    {
        cout << endl << e.what() << scan->getLineNumber();
    }

    catch (IdentifierBeginsWithNumberException& e)
    {
        cout << endl << e.what() << scan->getLineNumber();
    }

    catch (NoClosingCommentMarkException& e)
    {
        cout << endl << e.what() << scan->getLineNumber();
    }
}

