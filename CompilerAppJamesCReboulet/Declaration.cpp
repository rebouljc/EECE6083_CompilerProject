#include "Declaration.h"
#include "TerminalNode.h"
#include "ProcedureDeclaration.h"
#include "VariableDeclaration.h"
#include "TypeDeclaration.h"
#include "ArithOperatorsAreNotAValidTypeException.h"
#include "ExpressionOperatorsAreNotAValidTypeException.h"
#include "NoStringsAllowedInRelationalOperatorsException.h"
#include "StringLiteral.h"



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
			//this->verifyArithmeticOperationsAreCorrectlyDefinedPostDeclaration(it->first, it->second);
			bool itFirstIsIdentifier = false;
			bool itSecondIsIdentifier = false;

			bool itFirstIsRelation = false;
			bool itSecondIsRelation = false;

			//Need to check the value of tokenToCompare.
			if (dynamic_cast<Identifier*>(it->first) != nullptr)
			{
				if (dynamic_cast<Identifier*>(it->first)->getBitwiseAndOrOperationDefinedFlagValue())
				{
					itFirstIsIdentifier = true;
				}

				else if (dynamic_cast<Identifier*>(it->first)->getRelationPresentFlagValue())
				{
					itFirstIsRelation = true;
				}
			}

			else if (dynamic_cast<Number*>(it->first) != nullptr)
			{
				if (dynamic_cast<Number*>(it->first)->getBitwiseAndOrOperationDefinedFlagValue())
				{
					itFirstIsIdentifier = true;
				}

				else if (dynamic_cast<Number*>(it->first)->getRelationPresentFlagValue())
				{
					itFirstIsRelation = true;
				}
			}

			else if (dynamic_cast<StringLiteral*>(it->first) != nullptr)
			{
				if (dynamic_cast<StringLiteral*>(it->first)->getBitwiseAndOrOperationDefinedFlagValue())
				{
					itFirstIsIdentifier = true;
				}

				else if (dynamic_cast<StringLiteral*>(it->first)->getRelationPresentFlagValue())
				{
					itFirstIsRelation = true;
				}
			}

			if (dynamic_cast<Identifier*>(it->second) != nullptr)
			{
				if (dynamic_cast<Identifier*>(it->second)->getBitwiseAndOrOperationDefinedFlagValue())
				{
					itSecondIsIdentifier = true;
				}

				else if (dynamic_cast<Identifier*>(it->second)->getRelationPresentFlagValue())
				{
					itSecondIsRelation = true;
				}
			}

			else if (dynamic_cast<Number*>(it->second) != nullptr)
			{
				if (dynamic_cast<Number*>(it->second)->getBitwiseAndOrOperationDefinedFlagValue())
				{
					itSecondIsIdentifier = true;
				}

				else if (dynamic_cast<Number*>(it->second)->getRelationPresentFlagValue())
				{
					itSecondIsRelation = true;
				}

			}

			else if (dynamic_cast<StringLiteral*>(it->second) != nullptr)
			{
				if (dynamic_cast<StringLiteral*>(it->second)->getBitwiseAndOrOperationDefinedFlagValue())
				{
					itSecondIsIdentifier = true;
				}

				else if (dynamic_cast<StringLiteral*>(it->second)->getRelationPresentFlagValue())
				{
					itSecondIsRelation = true;
				}

			}
			if (itSecondIsIdentifier || itFirstIsIdentifier || itFirstIsRelation || itSecondIsRelation)
			{
				bool relationSet = false;
				if (itFirstIsRelation || itSecondIsRelation)
				{
					relationSet = true;
				}
				this->verifyExpressionOperationsAreCorrectlyDefinedPostDeclaration(it->first, it->second, relationSet);
			}

			else
			{

				this->verifyArithmeticOperationsAreCorrectlyDefinedPostDeclaration(it->first, it->second);
			}

		}
	
	
	

	this->tokenToCompare.clear();
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

void Declaration::verifyArithmeticOperationsAreCorrectlyDefined(Identifier* tokenToCompareLeft, Identifier* tokenToCompareRight,
	                                                            bool& leftTokInserted, bool& rightTokInserted)
{

	Identifier* symbolTableLeftTokValue;
	Identifier* symbolTableRightTokValue;
	string tokenToCompareLeftValue;
	string tokenToCompareRightValue;

	std::pair<ParseTreeNode*, ParseTreeNode*> pair;
	

	for (int s1 = 0; s1 < this->symbolTable.size(); ++s1)
	{

		if (
			dynamic_cast<Identifier*>(this->symbolTable.at(s1))->getNodeTokenValue() ==
			dynamic_cast<Identifier*>(tokenToCompareLeft)->getNodeTokenValue()
			)
		{
			pair.first = tokenToCompareLeft;
			//cout << "\nDeclaration: TokenToCompare->first = " << dynamic_cast<Identifier*>(pair.first)->getNodeTokenValue();
			leftTokInserted = true;
			
		}

		else if (
			     dynamic_cast<Identifier*>(this->symbolTable.at(s1))->getNodeTokenValue() ==
			     dynamic_cast<Identifier*>(tokenToCompareRight)->getNodeTokenValue() 
			    )
		{
			pair.second = tokenToCompareRight;
			//cout << "\nDeclaration: TokenToCompare->second = " << dynamic_cast<Identifier*>(pair.second)->getNodeTokenValue() << "\n\n";
			rightTokInserted = true;
		}

	}
	if (leftTokInserted)
	{
		pair.first = tokenToCompareLeft;
		
	}

	if (rightTokInserted)
	{
		pair.second = tokenToCompareRight;
		
	}

	if (leftTokInserted && rightTokInserted)
	{
		this->tokenToCompare.insert(pair);
		leftTokInserted = false;
		rightTokInserted = false;
	}	
}

void Declaration::verifyArithmeticOperationsAreCorrectlyDefinedNumberLeft(Number* tokenToCompareLeft, Identifier* tokenToCompareRight,
	                                                                      bool& leftTokInserted, bool& rightTokInserted)
{
	Identifier* symbolTableLeftTokValue;
	Identifier* symbolTableRightTokValue;
	string tokenToCompareLeftValue;
	string tokenToCompareRightValue;

	std::pair<ParseTreeNode*, ParseTreeNode*> pair;


	for (int s1 = 0; s1 < this->symbolTable.size(); ++s1)
	{

		if (
			dynamic_cast<Identifier*>(this->symbolTable.at(s1))->getNodeTokenValue() ==
			dynamic_cast<Identifier*>(tokenToCompareRight)->getNodeTokenValue()
			)
		{
			pair.first = tokenToCompareLeft;
			//cout << "\nDeclaration: TokenToCompare->first = " << dynamic_cast<Number*>(pair.first)->getNodeTokenValue() << "\n\n";
			leftTokInserted = true;

			pair.second = tokenToCompareRight;
			//cout << "\nDeclaration: TokenToCompare->second = " << dynamic_cast<Identifier*>(pair.second)->getNodeTokenValue() << "\n\n";
			rightTokInserted = true;

		}

	}
	if (leftTokInserted)
	{
		pair.first = tokenToCompareLeft;

	}

	if (rightTokInserted)
	{
		pair.second = tokenToCompareRight;

	}

	if (leftTokInserted && rightTokInserted)
	{
		this->tokenToCompare.insert(pair);
		leftTokInserted = false;
		rightTokInserted = false;
	}
}

void Declaration::verifyArithmeticOperationsAreCorrectlyDefinedNumberRight(Identifier* tokenToCompareLeft, Number* tokenToCompareRight,
	                                                                       bool& leftTokInserted, bool& rightTokInserted)
{
	Identifier* symbolTableLeftTokValue;
	Identifier* symbolTableRightTokValue;
	string tokenToCompareLeftValue;
	string tokenToCompareRightValue;

	std::pair<ParseTreeNode*, ParseTreeNode*> pair;


	for (int s1 = 0; s1 < this->symbolTable.size(); ++s1)
	{

		if (
			dynamic_cast<Identifier*>(this->symbolTable.at(s1))->getNodeTokenValue() ==
			dynamic_cast<Identifier*>(tokenToCompareLeft)->getNodeTokenValue()
			)
		{
			pair.first = tokenToCompareLeft;
			//cout << "\nDeclaration: TokenToCompare->first = " << dynamic_cast<Identifier*>(pair.first)->getNodeTokenValue() << "\n\n";
			leftTokInserted = true;

			pair.second = tokenToCompareRight;
			//cout << "\nDeclaration: TokenToCompare->second = " << dynamic_cast<Number*>(pair.second)->getNodeTokenValue() << "\n\n";
			rightTokInserted = true;

		}

	}
	if (leftTokInserted)
	{
		pair.first = tokenToCompareLeft;

	}

	if (rightTokInserted)
	{
		pair.second = tokenToCompareRight;

	}

	if (leftTokInserted && rightTokInserted)
	{
		this->tokenToCompare.insert(pair);
		leftTokInserted = false;
		rightTokInserted = false;
	}
}

void Declaration::verifyArithmeticOperationsAreCorrectlyDefinedPostDeclaration(ParseTreeNode* tokenToCompareLeft, ParseTreeNode* tokenToCompareRight)
{
	std::string leftValue = "";
	std::string rightValue = "";
	bool numberSet = false;
	
	
	try
	{
		if (tokenToCompareLeft != nullptr && tokenToCompareRight != nullptr)
		{
			//Now, we have to revert back to the ParseTree Method and start digging until we find a matching variable declaration.
			//I tried to avoid doing this, but it has to be done.  Recurse-Loop-Recurse-Loop-Repeat-Maybe crash too.
			

			this->verifyArithmeticOperationsAreCorrectlyDefinedDigAndBurnClockCycles(tokenToCompareLeft, tokenToCompareRight, leftValue, rightValue, numberSet);

			if (leftValue == "" || rightValue == "")
			{
				//throw an exception
				throw ArithOperatorsAreNotAValidTypeException();
			}

		}
	}
	catch (ArithOperatorsAreNotAValidTypeException &e)
	{
		if (leftValue == "")
		{
			cout << endl << endl << e.what() << dynamic_cast<Identifier*>(tokenToCompareLeft)->getNodeTokenLineNumber()
				 << " Identifier Name: " << dynamic_cast<Identifier*>(tokenToCompareLeft)->getNodeTokenValue();
		}

		if (rightValue == "")
		{
			cout << endl << endl << e.what() << dynamic_cast<Identifier*>(tokenToCompareRight)->getNodeTokenLineNumber()
				 << " Identifier Name: " << dynamic_cast<Identifier*>(tokenToCompareRight)->getNodeTokenValue();
		}
			
	}

}

void Declaration::verifyExpressionOperationsAreCorrectlyDefinedPostDeclaration(ParseTreeNode* tokenToCompareLeft, ParseTreeNode* tokenToCompareRight, bool &relationSet)
{
	std::string leftValue = "";
	std::string rightValue = "";
	bool numberSet = false;
	try
	{
		if (tokenToCompareLeft != nullptr && tokenToCompareRight != nullptr)
		{
			if (relationSet && dynamic_cast<Identifier*>(tokenToCompareLeft) != nullptr)
			{
				if (dynamic_cast<Identifier*>(tokenToCompareLeft)->getNoStringsAllowedFlagValue())
				{
					throw NoStringsAllowedInRelationOperatorsException();

				}
			}

			if (relationSet && dynamic_cast<Identifier*>(tokenToCompareRight) != nullptr)
			{
				if (dynamic_cast<Identifier*>(tokenToCompareRight)->getNoStringsAllowedFlagValue())
				{
					throw NoStringsAllowedInRelationOperatorsException();
				}
			}

			if (relationSet && dynamic_cast<StringLiteral*>(tokenToCompareLeft) != nullptr)
			{
				if (dynamic_cast<StringLiteral*>(tokenToCompareLeft)->getNoStringsAllowedFlagValue())
				{
					throw NoStringsAllowedInRelationOperatorsException();

				}
			}

			if (relationSet && dynamic_cast<StringLiteral*>(tokenToCompareRight) != nullptr)
			{
				if (dynamic_cast<StringLiteral*>(tokenToCompareRight)->getNoStringsAllowedFlagValue())
				{
					throw NoStringsAllowedInRelationOperatorsException();

				}
			}
		}
			
		
			//Now, we have to revert back to the ParseTree Method and start digging until we find a matching variable declaration.
			//I tried to avoid doing this, but it has to be done.  Recurse-Loop-Recurse-Loop-Repeat-Maybe crash too.


			this->verifyExpressionOperationsAreCorrectlyDefinedDigAndBurnClockCycles(tokenToCompareLeft, tokenToCompareRight, leftValue, rightValue, numberSet, relationSet);

			if (leftValue == "" || rightValue == "")
			{
				//throw an exception
				throw ExpressionOperatorsAreNotAValidTypeException();
			}

	}
	
	catch (ExpressionOperatorsAreNotAValidTypeException& e)
	{
		
		if(!relationSet)
		{
			if (leftValue == "")
			{
				cout << endl << endl << e.what() << dynamic_cast<Identifier*>(tokenToCompareLeft)->getNodeTokenLineNumber()
					<< " Identifier Name: " << dynamic_cast<Identifier*>(tokenToCompareLeft)->getNodeTokenValue();
			}

			if (rightValue == "")
			{
				cout << endl << endl << e.what() << dynamic_cast<Identifier*>(tokenToCompareRight)->getNodeTokenLineNumber()
					<< " Identifier Name: " << dynamic_cast<Identifier*>(tokenToCompareRight)->getNodeTokenValue();
			}
		}

	}

	catch (NoStringsAllowedInRelationOperatorsException& e)
	{
		if (leftValue == "")
		{
			if (dynamic_cast<Identifier*>(tokenToCompareLeft) != nullptr)
			{
				cout << endl << endl << e.what() << dynamic_cast<Identifier*>(tokenToCompareLeft)->getNodeTokenLineNumber()
					<< " Identifier Name: " << dynamic_cast<Identifier*>(tokenToCompareLeft)->getNodeTokenValue();
			}
			else if (dynamic_cast<StringLiteral*>(tokenToCompareLeft) != nullptr)
			{
				cout << endl << endl << e.what() << dynamic_cast<StringLiteral*>(tokenToCompareLeft)->getNodeTokenLineNumber()
					<< " String Literal Value: " << dynamic_cast<StringLiteral*>(tokenToCompareLeft)->getNodeTokenValue();
			}
		}

		if (rightValue == "")
		{
			if (dynamic_cast<Identifier*>(tokenToCompareRight) != nullptr)
			{
				cout << endl << endl << e.what() << dynamic_cast<Identifier*>(tokenToCompareRight)->getNodeTokenLineNumber()
					<< " Identifier Name: " << dynamic_cast<Identifier*>(tokenToCompareRight)->getNodeTokenValue();
			}
			else if (dynamic_cast<StringLiteral*>(tokenToCompareRight) != nullptr)
			{
				cout << endl << endl << e.what() << dynamic_cast<StringLiteral*>(tokenToCompareRight)->getNodeTokenLineNumber()
					<< " String Literal Value: " << dynamic_cast<StringLiteral*>(tokenToCompareRight)->getNodeTokenValue();
			}
		}
	}



}
