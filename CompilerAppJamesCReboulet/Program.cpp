#include "Program.h"
#include "ProgramHeader.h"
#include "ProgramBody.h"
#include "TerminalNode.h"
#include "Token.h"



Program::Program(Parser* parser)
{
	
	this->setParserPtr(parser);
	this->verifySyntaxCreateParseTree(0, this);

	for (set<pair<ParseTreeNode*, ParseTreeNode*>>::iterator it = this->tokenToCompare.begin(); it != this->tokenToCompare.end(); ++it)
	{
		this->verifyArithmeticOperationsAreCorrectlyDefinedPostDeclaration(it->first, it->second);
	}
	
}

void Program::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{
	//always make sure to pass the parser ptr.
	//create a program header.
	this->linkedMemberNonterminals.push_back(new ProgramHeader(this->parserPtr, motherNode, this)); //If any of these operations fail, an exception will be thrown and 
	                                                                              //this method won't complete.  At the first instance of failure,
	                                                                              //exceptions will be thrown, unless we can detect and recover from all
	                                                                              //failures and throw one giant exception at the end with all of the errors.

	this->linkedMemberNonterminals.push_back(new ProgramBody(this->parserPtr, motherNode, this));
	Token* currentToken = nullptr;
	
	currentToken = this->parserPtr->readNextToken();
	
	if (currentToken->getTokenValue() == ".") //Note, this isn't going to work correctly until we have defined the program body.  Never will be hit!
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
	}
	

	

	else
	{
		//Throw the exception and have the user add the period.  Also, spit out a list of all of the other errors that have accumulated,
		//unless a critical error occurs that is not recoverable.  This program will not recover from errors detected in the Scanner,
		//since we do not want any junk making it into the parser (i.e. comments interpreted as identifiers and/or punctuation) and 
		//infinite recursion in the scanner.  C++ is not too friendly when it comes to parsing text, so the Scanner had to do it perfectly.
		//We don't want to risk skipping over tokens and having a disconnect between what the user instructs the compiler/computer to do
		//and what the computer actually does.  That resembles the old Fortran compilers and is very bad! The programmer needs total control,
		//and the computer should be 100% predictable as long as the programmer is not an idiot - can't do anything about that.
	}
}
ParseTreeNode* Program::getNodePtr()
{
	return this;
}

void Program::populateSearchResultsList(ParseTreeNode* motherNode)
{
	motherNode = this;

	

	for (unsigned int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}

void Program::verifyArithmeticOperationsAreCorrectlyDefined(Identifier* tokenToCompareLeft, Identifier* tokenToCompareRight)
{

	Identifier* symbolTableLeftTokValue;
	Identifier* symbolTableRightTokValue;
	string tokenToCompareLeftValue;
	string tokenToCompareRightValue;

	std::pair<ParseTreeNode*, ParseTreeNode*> pair;

	for (int s1 = 0; s1 < this->symbolTable.size(); ++s1)
	{

		if (dynamic_cast<Identifier*>(this->symbolTable.at(s1))->getNodeTokenValue() ==
			dynamic_cast<Identifier*>(tokenToCompareLeft)->getNodeTokenValue()
			)
		{

			pair.first = tokenToCompareLeft;

		}

		else if (dynamic_cast<Identifier*>(this->symbolTable.at(s1))->getNodeTokenValue() ==
			dynamic_cast<Identifier*>(tokenToCompareRight)->getNodeTokenValue()
			)
		{
			pair.second = tokenToCompareRight;
		}
	}

	this->tokenToCompare.insert(pair);
}

void Program::verifyArithmeticOperationsAreCorrectlyDefinedPostDeclaration(ParseTreeNode* tokenToCompareLeft, ParseTreeNode* tokenToCompareRight)
{
	if (tokenToCompareLeft != nullptr && tokenToCompareRight != nullptr)
	{
		//Now, we have to revert back to the ParseTree Method and start digging until we find a matching variable declaration.
		//I tried to avoid doing this, but it has to be done.  Recurse-Loop-Recurse-Loop-Repeat-Maybe crash too.
		std::string leftValue = "";
		std::string rightValue = "";
		this->verifyArithmeticOperationsAreCorrectlyDefinedDigAndBurnClockCycles(tokenToCompareLeft, tokenToCompareRight, leftValue, rightValue);



	}

	else
	{
		//We 
	}
}





