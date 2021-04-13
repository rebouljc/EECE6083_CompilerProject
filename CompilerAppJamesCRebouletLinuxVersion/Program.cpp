#include "Program.h"
#include "ProgramHeader.h"
#include "ProgramBody.h"
#include "TerminalNode.h"
#include "Token.h"
#include "ArithOperatorsAreNotAValidTypeException.h"
#include "ExpressionOperatorsAreNotAValidTypeException.h"
#include "NoStringsAllowedInRelationalOperatorsException.h"
#include "IllegalRelationalOperatorComparisonOfIntegerFloatWithStringException.h"
#include "IfAndForLoopsMustReturnABooleanValueStringException.h"




Program::Program(Parser* parser)
{
	
	this->setParserPtr(parser);
	this->verifySyntaxCreateParseTree(0, this);

	
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

			else if (dynamic_cast<Identifier*>(it->first)->getRelationPresentFlagValue() ||
				     dynamic_cast<Identifier*>(it->first)->getSingleVariableIfLoopExpressionFlag()
				    )
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

			else if (dynamic_cast<Number*>(it->first)->getRelationPresentFlagValue() ||
				     dynamic_cast<Number*>(it->first)->getSingleVariableIfLoopExpressionFlag()
				    )
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

			else if (dynamic_cast<StringLiteral*>(it->first)->getRelationPresentFlagValue() ||
				     dynamic_cast<Identifier*>(it->first)->getSingleVariableIfLoopExpressionFlag()
				    )
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

void Program::verifyArithmeticOperationsAreCorrectlyDefined(Identifier* tokenToCompareLeft, Identifier* tokenToCompareRight,
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
			
			//cout << "\nDeclaration: TokenToCompare->second = " << dynamic_cast<Identifier*>(pair.second)->getNodeTokenValue();
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

void Program::verifyArithmeticOperationsAreCorrectlyDefinedNumberLeft(Number* tokenToCompareLeft, Identifier* tokenToCompareRight,
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

void Program::verifyArithmeticOperationsAreCorrectlyDefinedNumberRight(Identifier* tokenToCompareLeft, Number* tokenToCompareRight,
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

void Program::verifyStringOperationsAreCorrectlyDefined(Identifier* tokenToCompareLeftIdentifier, StringLiteral* tokenToCompareLeftStringLiteral,
	                                                    Number* tokenToCompareLeftNumber)
{
	std::pair<ParseTreeNode*, ParseTreeNode*> pair;

	if (tokenToCompareLeftIdentifier != nullptr)
	{
		pair.first = tokenToCompareLeftIdentifier;
		this->tokenToCompare.insert(pair);
	}

	else if (tokenToCompareLeftStringLiteral != nullptr)
	{
		pair.first = tokenToCompareLeftStringLiteral;
		this->tokenToCompare.insert(pair);
	}

	else if (tokenToCompareLeftNumber != nullptr)
	{
		pair.first = tokenToCompareLeftNumber;
		this->tokenToCompare.insert(pair);
	}
}

void Program::verifyArithmeticOperationsAreCorrectlyDefinedStringLiteralLeft(StringLiteral* tokenToCompareLeft, Identifier* tokenToCompareRight,
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

void Program::verifyArithmeticOperationsAreCorrectlyDefinedStringLiteralRight(Identifier* tokenToCompareLeft, StringLiteral* tokenToCompareRight,
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

void Program::verifyArithmeticOperationsAreCorrectlyDefinedPostDeclaration(ParseTreeNode* tokenToCompareLeft, ParseTreeNode* tokenToCompareRight)
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
				throw ArithOperatorsAreNotAValidTypeException();
			}

		}
	}
	catch (ArithOperatorsAreNotAValidTypeException& e)
	{
		if (leftValue == "")
		{
			cout << endl << endl << e.what() << dynamic_cast<Identifier*>(tokenToCompareLeft)->getNodeTokenLineNumber()
				 << " Identifier Name: " << dynamic_cast<Identifier*>(tokenToCompareLeft)->getNodeTokenValue();

			//Flag the compiler to not proceed with Intermediate-Code Generation if unresolved compiler errors are present but not to crap out.
			this->parserPtr->setCompilerErrorsPresentFlag(true);
		}

		if (rightValue == "")
		{
			cout << endl << endl << e.what() << dynamic_cast<Identifier*>(tokenToCompareRight)->getNodeTokenLineNumber()
				 << " Identifier Name: " << dynamic_cast<Identifier*>(tokenToCompareRight)->getNodeTokenValue();

			//Flag the compiler to not proceed with Intermediate-Code Generation if unresolved compiler errors are present but not to crap out.
			this->parserPtr->setCompilerErrorsPresentFlag(true);
		}

		

	}

}


void Program::verifyExpressionOperationsAreCorrectlyDefinedPostDeclaration(ParseTreeNode* tokenToCompareLeft, ParseTreeNode* tokenToCompareRight, bool &relationSet)
{
	
		std::string leftValue = "";
		std::string rightValue = "";
		bool numberSet = false;
		try
		{
			Identifier* ident = nullptr;
			StringLiteral* str = nullptr;
			Number* num = nullptr;

			if ((ident = dynamic_cast<Identifier*>(tokenToCompareLeft)) != nullptr && ident->getSingleVariableIfLoopExpressionFlag())
			{
				this->verifyExpressionOperationsAreCorrectlyDefinedDigAndBurnClockCycles(tokenToCompareLeft, tokenToCompareRight, leftValue, rightValue, numberSet, relationSet);
			}

			if ((str = dynamic_cast<StringLiteral*>(tokenToCompareLeft)) != nullptr && str->getSingleVariableIfLoopExpressionFlag())
			{
				this->verifyExpressionOperationsAreCorrectlyDefinedDigAndBurnClockCycles(tokenToCompareLeft, tokenToCompareRight, leftValue, rightValue, numberSet, relationSet);
			}

			if ((num = dynamic_cast<Number*>(tokenToCompareLeft)) != nullptr && num->getSingleVariableIfLoopExpressionFlag())
			{
				this->verifyExpressionOperationsAreCorrectlyDefinedDigAndBurnClockCycles(tokenToCompareLeft, tokenToCompareRight, leftValue, rightValue, numberSet, relationSet);
			}

			if (tokenToCompareLeft != nullptr && tokenToCompareRight != nullptr)
			{
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



				//Now, we have to revert back to the ParseTree Method and start digging until we find a matching variable declaration.
				//I tried to avoid doing this, but it has to be done.  Recurse-Loop-Recurse-Loop-Repeat-Maybe crash too.

				this->verifyExpressionOperationsAreCorrectlyDefinedDigAndBurnClockCycles(tokenToCompareLeft, tokenToCompareRight, leftValue, rightValue, numberSet, relationSet);

				if (leftValue == "" || rightValue == "")
				{
					throw ExpressionOperatorsAreNotAValidTypeException();
				}
				

				if (relationSet && dynamic_cast<Identifier*>(tokenToCompareLeft) != nullptr)
				{

					if (dynamic_cast<Identifier*>(tokenToCompareLeft)->getNoStringsAllowedFlagValue() && leftValue == "string")
					{
						throw NoStringsAllowedInRelationOperatorsException();

					}
				}

				if (relationSet && dynamic_cast<Identifier*>(tokenToCompareRight) != nullptr && rightValue == "string")
				{
					if (dynamic_cast<Identifier*>(tokenToCompareRight)->getNoStringsAllowedFlagValue())
					{
						throw NoStringsAllowedInRelationOperatorsException();

					}
				}

			}
		}
		catch (ExpressionOperatorsAreNotAValidTypeException& e)
		{
			if (!relationSet)
			{
				
				if (leftValue == "")
				{
					cout << endl << endl << e.what() << dynamic_cast<Identifier*>(tokenToCompareLeft)->getNodeTokenLineNumber()
						<< " Identifier Name: " << dynamic_cast<Identifier*>(tokenToCompareLeft)->getNodeTokenValue();

					//Flag the compiler to not proceed with Intermediate-Code Generation if unresolved compiler errors are present but not to crap out.
					this->parserPtr->setCompilerErrorsPresentFlag(true);
				}

				if (rightValue == "")
				{
					cout << endl << endl << e.what() << dynamic_cast<Identifier*>(tokenToCompareRight)->getNodeTokenLineNumber()
						<< " Identifier Name: " << dynamic_cast<Identifier*>(tokenToCompareRight)->getNodeTokenValue();

					//Flag the compiler to not proceed with Intermediate-Code Generation if unresolved compiler errors are present but not to crap out.
					this->parserPtr->setCompilerErrorsPresentFlag(true);
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

					//Flag the compiler to not proceed with Intermediate-Code Generation if unresolved compiler errors are present but not to crap out.
					this->parserPtr->setCompilerErrorsPresentFlag(true);
				}

				else if (dynamic_cast<StringLiteral*>(tokenToCompareLeft) != nullptr)
				{
					cout << endl << endl << e.what() << dynamic_cast<StringLiteral*>(tokenToCompareLeft)->getNodeTokenLineNumber()
						<< " String Literal Value: " << dynamic_cast<StringLiteral*>(tokenToCompareLeft)->getNodeTokenValue();

					//Flag the compiler to not proceed with Intermediate-Code Generation if unresolved compiler errors are present but not to crap out.
					this->parserPtr->setCompilerErrorsPresentFlag(true);
				}

				this->parserPtr->setCompilerErrorsPresentFlag(true);
			}

			if (rightValue == "")
			{
				if (dynamic_cast<Identifier*>(tokenToCompareRight) != nullptr)
				{
					cout << endl << endl << e.what() << dynamic_cast<Identifier*>(tokenToCompareRight)->getNodeTokenLineNumber()
						<< " Identifier Name: " << dynamic_cast<Identifier*>(tokenToCompareRight)->getNodeTokenValue();

					//Flag the compiler to not proceed with Intermediate-Code Generation if unresolved compiler errors are present but not to crap out.
					this->parserPtr->setCompilerErrorsPresentFlag(true);
				}
				else if (dynamic_cast<StringLiteral*>(tokenToCompareRight) != nullptr)
				{
					cout << endl << endl << e.what() << dynamic_cast<StringLiteral*>(tokenToCompareRight)->getNodeTokenLineNumber()
						<< " String Literal Value: " << dynamic_cast<StringLiteral*>(tokenToCompareRight)->getNodeTokenValue();

					//Flag the compiler to not proceed with Intermediate-Code Generation if unresolved compiler errors are present but not to crap out.
					this->parserPtr->setCompilerErrorsPresentFlag(true);
				}
			}
			
		}
		catch (IllegalRelationalOperatorComparisonOfIntegerFloatWithStringException& e)
		{
			
			if (dynamic_cast<Identifier*>(tokenToCompareLeft) != nullptr)
			{
				cout << endl << endl << e.what() << dynamic_cast<Identifier*>(tokenToCompareLeft)->getNodeTokenLineNumber()
					 << " Identifier Name: " << dynamic_cast<Identifier*>(tokenToCompareLeft)->getNodeTokenValue();

				//Flag the compiler to not proceed with Intermediate-Code Generation if unresolved compiler errors are present but not to crap out.
				this->parserPtr->setCompilerErrorsPresentFlag(true);
			}

			if (dynamic_cast<StringLiteral*>(tokenToCompareLeft) != nullptr)
			{
				cout << endl << endl << e.what() << dynamic_cast<StringLiteral*>(tokenToCompareLeft)->getNodeTokenLineNumber()
					 << " String Literal Value: " << dynamic_cast<StringLiteral*>(tokenToCompareLeft)->getNodeTokenValue();

				//Flag the compiler to not proceed with Intermediate-Code Generation if unresolved compiler errors are present but not to crap out.
				this->parserPtr->setCompilerErrorsPresentFlag(true);
			}
			
			if (dynamic_cast<Identifier*>(tokenToCompareRight) != nullptr)
			{
				cout << endl << endl << e.what() << dynamic_cast<Identifier*>(tokenToCompareRight)->getNodeTokenLineNumber()
					 << " Identifier Name: " << dynamic_cast<Identifier*>(tokenToCompareRight)->getNodeTokenValue();

				//Flag the compiler to not proceed with Intermediate-Code Generation if unresolved compiler errors are present but not to crap out.
				this->parserPtr->setCompilerErrorsPresentFlag(true);
			}

			if (dynamic_cast<StringLiteral*>(tokenToCompareRight) != nullptr)
			{
				cout << endl << endl << e.what() << dynamic_cast<StringLiteral*>(tokenToCompareRight)->getNodeTokenLineNumber()
					 << " String Literal Value: " << dynamic_cast<StringLiteral*>(tokenToCompareRight)->getNodeTokenValue();

				//Flag the compiler to not proceed with Intermediate-Code Generation if unresolved compiler errors are present but not to crap out.
				this->parserPtr->setCompilerErrorsPresentFlag(true);
			}
			
			
		}

		catch (IfAndForLoopsMustReturnABooleanValueException& e)
		{
			if (dynamic_cast<Identifier*>(tokenToCompareLeft) != nullptr)
			{
				cout << endl << endl << e.what() << dynamic_cast<Identifier*>(tokenToCompareLeft)->getNodeTokenLineNumber()
					<< " Identifier Name: " << dynamic_cast<Identifier*>(tokenToCompareLeft)->getNodeTokenValue();

				//Flag the compiler to not proceed with Intermediate-Code Generation if unresolved compiler errors are present but not to crap out.
				this->parserPtr->setCompilerErrorsPresentFlag(true);
			}

			if (dynamic_cast<StringLiteral*>(tokenToCompareLeft) != nullptr)
			{
				cout << endl << endl << e.what() << dynamic_cast<StringLiteral*>(tokenToCompareLeft)->getNodeTokenLineNumber()
					<< " String Literal Value: " << dynamic_cast<StringLiteral*>(tokenToCompareLeft)->getNodeTokenValue();

				//Flag the compiler to not proceed with Intermediate-Code Generation if unresolved compiler errors are present but not to crap out.
				this->parserPtr->setCompilerErrorsPresentFlag(true);
			}

			if (dynamic_cast<Number*>(tokenToCompareLeft) != nullptr)
			{
				cout << endl << endl << e.what() << dynamic_cast<Number*>(tokenToCompareLeft)->getNodeTokenLineNumber()
					 << " Floating-Point-Literal Value: " << dynamic_cast<Number*>(tokenToCompareLeft)->getNodeTokenIntegerDoubleNumberTokenValue();

				//Flag the compiler to not proceed with Intermediate-Code Generation if unresolved compiler errors are present but not to crap out.
				this->parserPtr->setCompilerErrorsPresentFlag(true);
			}

			
		}
	
	
	
	
	

}





