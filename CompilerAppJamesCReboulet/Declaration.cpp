#include "Declaration.h"
#include "TerminalNode.h"
#include "ProcedureDeclaration.h"
#include "VariableDeclaration.h"
#include "TypeDeclaration.h"


/*NOTE:  REMEMBER TO CALL this->parserPtr->backupIndexToRead() if a recursive function pops a newly created object from the vector.
  Otherwise, that particular token will have already been read and it will be ignored in future methods/classes that need it.*/

Declaration::Declaration(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr)
{
	//Note: 3-13-2021: Added additional statement to set this node's parent node ptr, to enable reverse walking back up a tree.
	this->parentNodePtr = parentNodePtr;
	this->setParserPtr(parser);
	this->programNode_motherNode = motherNode;
	this->verifySyntaxCreateParseTree(0, motherNode);

	for (set<pair<ParseTreeNode*, ParseTreeNode*>>::iterator it = this->tokenToCompare.begin(); it != this->tokenToCompare.end(); ++it)
	{
		this->verifyArithmeticOperationsAreCorrectlyDefinedPostDeclaration(it->first, it->second);
	}
}

bool Declaration::checkGlobalTerminalNodePresent()
{
	TerminalNode* termNode;
	if (!this->linkedMemberNonterminals.empty() && 
		(termNode = dynamic_cast<TerminalNode*>(this->linkedMemberNonterminals.at(0))) != nullptr &&
		 termNode->getNodeTokenValue() == "global"
	   )
	{
		return true;
	}
	return false;
}
void Declaration::verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode)
{   //Needs to be modified for program body.  Make it recursive to handle multiple declarations and statements.
	Token* currentToken = this->parserPtr->getCurrentlyReadToken();
	//printf("\nDeclaration_CurrentToken = %s", currentToken->getTokenValue().c_str());
	
	bool varDeclFlag = false;
	bool procDeclFlag = false;
	bool typeDeclFlag = false;
	if (currentToken->getTokenValue() == "global")
	{
		this->linkedMemberNonterminals.push_back(new TerminalNode(currentToken, this));
		currentToken = this->parserPtr->readNextToken();  //This will store the currently read token in parserPtr, even though it returns a useless Token* here.
		++tokenCounter; //Increment the token counter, so that if the word "global" is present, there should be at least 1 declaration.
		this->verifySyntaxCreateParseTree(tokenCounter, motherNode);
	}

	else
	{   
		
		this->linkedMemberNonterminals.push_back(new ProcedureDeclaration(this->parserPtr, motherNode, this));
		//Get rid of the node if there is nothing there, so it doesn't have to be included in the parse tree.
		ParseTreeNode* decl = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);
		if (!decl->getIsValid())
		{
			this->linkedMemberNonterminals.pop_back();
			
			
		}
		else
		{
			this->setIsValid(true);
			
			
			return; //If one is true, there is no reason to test any more of them.  The call stack gets way too big.

		}
		this->linkedMemberNonterminals.push_back(new VariableDeclaration(this->parserPtr, motherNode, this));
		decl = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);
		if (!decl->getIsValid())
		{
			this->linkedMemberNonterminals.pop_back();
			
			
		}
		else
		{
			this->setIsValid(true);

			return; //If one is true, there is no reason to test any more of them.  The call stack gets way too big.
		}
		this->linkedMemberNonterminals.push_back(new TypeDeclaration(this->parserPtr, motherNode, this));
		decl = this->linkedMemberNonterminals.at(this->linkedMemberNonterminals.size() - 1);
		if (!decl->getIsValid())
		{
			this->linkedMemberNonterminals.pop_back();
			
			
		}
		else
		{
			this->setIsValid(true);
			return; //If one is true, there is no reason to test any more of them.  The call stack gets way too big.
		}
		
	}

	//Else, we will return with a value of false and the Program Body class will pop the declaration off of the stack.
	//We will do the same thing here for statements, since there is the option of having a program with neither declarations or statements.
	
	return;

}

ParseTreeNode* Declaration::getNodePtr()
{
	return this;

}

void Declaration::populateSearchResultsList(ParseTreeNode* motherNode)
{


	for (unsigned int i = 0; i < this->linkedMemberNonterminals.size(); ++i)
	{
		this->linkedMemberNonterminals.at(i)->populateSearchResultsList(motherNode);
	}

	motherNode->addToSearchResultsList(this->getNodePtr());
}

void Declaration::verifyArithmeticOperationsAreCorrectlyDefined(Identifier* tokenToCompareLeft, Identifier* tokenToCompareRight)
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
	cout << "\nTokenToCompare->first = " << pair.first;
	cout << "\nTokenToCompare->second = " << pair.second;
}

void Declaration::verifyArithmeticOperationsAreCorrectlyDefinedPostDeclaration(ParseTreeNode* tokenToCompareLeft, ParseTreeNode* tokenToCompareRight)
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
