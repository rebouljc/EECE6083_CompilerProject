#include "Parser.h"
#include "Program.h"
#include "IntermediateCodeGenerator.h"
#include "IdentifierNotDeclaredException.h"
#include "MainCompileErrorException.h"




Parser::Parser()
{
    
}
void Parser::init()
{
    try
    {
        

        ((Scanner*)(this))->init();

        this->populatePredefinedRuntimeProceduresList();
    }

    //Scanner Exceptions
    catch (MainCompileErrorException& e)
    {
        cout << endl << e.what() << endl;
        //This is also a bad error - forgetting to surround a string literal with " marks.
        //We must crap out on this as well, since it can't be determined until the scanner reads the entire file
        //with an eof() and the tokens are not parsed correctly at all.
        this->setCompilerErrorsPresentFlag(true);
        return;
    }

    catch (NoClosingCommentMarkException& e)
    {
        cout << endl << e.what() << this->getFirstCommentLineNumber();
        //This is bad: We cannot recover or synchronize from this error,
        //since it cannot be detected until scanning is complete and 
        //there is nothing in the token list, so we must throw a main exception and stop everything altogether, or things will turn ugly.
        //Don't make this error, or this compiler will have something to say about it!

        
        //Here, we crap out, but we clean up the memory mess first, since we cannot recover with this type of error.
        this->setCompilerErrorsPresentFlag(true);
        throw MainCompileErrorException();
        return;

    }

    //Other exceptions can be fixed and resynchronization can take place, but the two above are unrecoverable.

    this->parseTokensLoop();
  
    

    //Parser Exceptions

    //Semantic-Analyzer Exceptions

}

void Parser::populatePredefinedRuntimeProceduresList()
{
    if (this->predefinedRuntimeFunctionsList == nullptr)
    {
        this->predefinedRuntimeFunctionsList = new vector<string>();
    }
    this->predefinedRuntimeFunctionsList->push_back("getbool");
    this->predefinedRuntimeFunctionsList->push_back("getinteger");
    this->predefinedRuntimeFunctionsList->push_back("getfloat");
    this->predefinedRuntimeFunctionsList->push_back("getstring");
    this->predefinedRuntimeFunctionsList->push_back("putbool");
    this->predefinedRuntimeFunctionsList->push_back("putinteger");
    this->predefinedRuntimeFunctionsList->push_back("putfloat");
    this->predefinedRuntimeFunctionsList->push_back("putstring");
    this->predefinedRuntimeFunctionsList->push_back("sqrt");

}

bool Parser::searchPredefinedRuntimeProceduresList(std::string queryName)
{
    for (int i = 0; i < this->predefinedRuntimeFunctionsList->size(); ++i)
    {
        if (this->predefinedRuntimeFunctionsList->at(i) == queryName)
        {
            return true;
        }
    }

    return false;
}

Token* Parser::getCurrentlyReadToken()
{
    return this->currentReadToken;
}
Parser::~Parser()
{
   

    for (unsigned int i = 0; i < this->storedTokens.size(); ++i)
    {
        delete (this->storedTokens.at(i));
        
    }
    this->storedTokens.clear();
    this->cleanUp();
    
   
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

    this->currentReadToken = tokToReturn;
    return tokToReturn;
}

void Parser::resetTokenReadIndexToPrevious()
{
    if (this->indexToRead > 0)
    {
        -- this->indexToRead;
    }
}
void Parser::parseTokensLoop()
{
    //create the parse tree
    ParseTreeNode* parseTree = nullptr;
   
       parseTree = new Program(this);
    //This is the first node of the linked list.  I will create a class for each of the non-terminals in the grammar.
    //Now program will contain its terminal tokens and non-terminal classes which all inherit from ParseTreeNode* abstract class.
    //If I want to now search the entire tree, I will create a separate pointer and cast the Program Pointer to a parseTree. 
    //create a virtual search method in each class and return a pointer to that object when the 
                                          //search method is called.  
   
   
    ((IntermediateCodeGenerator*)(this))->setParseTreePtr(parseTree);
    

    



    //Currently, search is a depth-first search of the parseTree.  Put this in intermediate code generator.   

    //Call the intermediate code generator from here.  This is all we can do, since we can't store the linked list globally. 
    //We need this dependency, unfortunately or we risk violating the encapsulation principle of OOP.  
    
    //IntermediateCodeGenerator* intermediate = new IntermediateCodeGenerator(parseTree);
    
    //Now, we have to clean up the memory to fix memory leaks.
    
    
    

    
    //delete (intermediate);
    
}


    
