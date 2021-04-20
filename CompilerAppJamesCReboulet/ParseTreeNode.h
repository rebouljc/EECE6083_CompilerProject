#pragma once
#include <vector>
#include "Token.h"
#include "Parser.h"
#include "stdlib.h"


class ParseTreeNode
{
public:
	
	vector<ParseTreeNode*>* getSearchResultsList(ParseTreeNode* currentProgramNodePtr);
	
	void addToSearchResultsList(ParseTreeNode* nodeToAdd);
	bool addToSymbolTable(ParseTreeNode* symbolToAdd, bool checkUnique);
	bool searchSymbolTable(ParseTreeNode* searchSymbol, ParseTreeNode* returnSymbol);
	virtual void populateSearchResultsList(ParseTreeNode* motherNode = nullptr) { return; };
	vector<ParseTreeNode*>* getSymbolTable();
	virtual void setIsValid(bool isValid) {};
	virtual bool getIsValid() { return false; };
	void setParserPtr(Parser* parserPtr);
	virtual ~ParseTreeNode() {};
	virtual bool checkGlobalTerminalNodePresent() { return false; };
	void climbTreeAndPopulateSymbolTable(string identifierType, ParseTreeNode* identifierNode);
	void climbTreeAndSetParenthesesPresentOnExpressionFlag();
	bool climbTreeAndCheckParenthesesPresentOnParentExpressionFlag(bool& calledFromExpression, bool &parenthesesPresentFlag);
	virtual void generateIntermediateCodeFromParseTree(ofstream* outputFileStream, vector<ParseTreeNode*>* declSymbolTablePtr) { return; };
	ParseTreeNode* getParentNodePtr() { return this->parentNodePtr; };

	
	//Get linkedNonterminals for semantic check
	vector<ParseTreeNode*>& getLinkedMemberNonterminalsList();

	//Intermediate Code Generation Public Methods.
	void ICGenerationIfStatementDigAndCollectRightAndLeftOperands();
	ParseTreeNode* ICGenerationIfStatementDigAndCollectLeftOperand();
	ParseTreeNode* ICGenerationIfStatementDigAndCollectRightOperand();

	void setRightOperandPtr(ParseTreeNode* right) { this->rightOperand = right; };
	void setLeftOperandPtr(ParseTreeNode* left) { this->leftOperand = left; };
	ParseTreeNode* getRightOperandPtr() { return this->rightOperand; };
	ParseTreeNode* getLeftOperandPtr() { return this->leftOperand; };
	void ICCodeGenerationSendIfStatementOperandsUpTheChainToParentIfStatement(ParseTreeNode* left, ParseTreeNode* right);
	int ICCodeGenerationClimbTreeToProcedureBodyAndGetIndexValue();
	void ICCodeGenerationClimbTreeToProcedureBodyAndIncrementIndexValue();


	//There were too many public methods popping up here, which were specific to semantic analysis,
	//and should only be available to this class and its children.  Otherwise, too many possibilities for problems.  
	

protected:
	//methods
	
	virtual ParseTreeNode* getNodePtr() { return nullptr; };
	virtual void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode = nullptr) { return; };

	bool searchLocalSymbolTable(ParseTreeNode* searchSymbol, ParseTreeNode* returnSymbol,
		vector<ParseTreeNode*>* symbolTablePtr
	);

	bool ICGenerationClimbTreeAndCheckForReturnStatement();
	
	
	

	//Protected Semantic-Checking Methods.

	//Tree climbing methods for semantic verification.
	void climbTreeAndVerifyArrayIndices(ParseTreeNode* numberNode);

	
	//Additional methods for semantic checking.

	void climbTreeAndVerifyArithmeticOperationsAreCorrectlyDefined(ParseTreeNode* tokenToCompare, bool numberSet);
	void climbTreeAndVerifyRelationOperationsAreCorrectlyDefined(ParseTreeNode* tokenToCompare, bool numberSet,
	                                                             bool &relationPresentFlag, 
		                                                         bool &setRelationPresentFlag);
	void climbTreeAndVerifyTermOperationsAreCorrectlyDefined(ParseTreeNode* tokenToCompare, bool numberSet);
	void climbTreeAndVerifyExpressionOperationsAreCorrectlyDefined(ParseTreeNode* tokenToCompare, bool numberSet,
		                                                           bool& expressionPresentFlag, bool& singleVariableIfLoopExpressionPresent
	                                                              );
	void verifyArithmeticOperationsAreCorrectlyDefinedDigAndBurnClockCycles(ParseTreeNode* tokenToCompareLeft, ParseTreeNode* tokenToCompareRight,
		                                                                    std::string &leftValue, std::string &rightValue, bool& numberSet);
	void verifyExpressionOperationsAreCorrectlyDefinedDigAndBurnClockCycles(ParseTreeNode* tokenToCompareLeft, ParseTreeNode* tokenToCompareRight,
		std::string& leftValue, std::string& rightValue, bool& numberSet, bool& relationSet);

	void climbTreeToDeclarationAndVerifyArithmeticOperationsAreCorrectlyDefined(ParseTreeNode* tokenToCompareLeft,
		ParseTreeNode* tokenToCompareRight,
		bool& leftTokInserted, bool& rightTokInserted,
		bool& expressionPresentFlag,
		bool& relationPresentFlag,
		bool& setForOrIfStatementPresentFlag,
		bool& singleVariableIfLoopExpressionPresent
	);

#define OUT 0
#ifndef OUT
	void climbTreeToNearestExpressionAndSetParenthesesFlag();
#endif	
	
	
	//member variables
	
	Parser* parserPtr = nullptr;
	ParseTreeNode* parentNodePtr;
	vector<ParseTreeNode*> searchResultsList;
	//vector<ParseTreeNode*> symbolTable;
	string localClassType;
	vector<ParseTreeNode*> symbolTable; //symbolTable.first = TablePtr symbolTable.second == IdentifierPtr 
	ParseTreeNode* programNode_motherNode = nullptr;
	vector<ParseTreeNode*> linkedMemberNonterminals;
	std::set<pair<ParseTreeNode*, ParseTreeNode*>> tokenToCompare;

private:
	
	//We don't want this function to be global, since we want to make sure we don't set numberNode and IdentifierNode
	//to a null pointer, which could potentially happen if it is global.
	void climbTreeToDeclarationNode(ParseTreeNode* identifierNode);
	//Private Semantic Checking Methods
	void checkArrayIndexInBounds(ParseTreeNode &identifier, ParseTreeNode &symbolTableIdentifier);
	ParseTreeNode* rightOperand = nullptr;
	ParseTreeNode* leftOperand = nullptr;

	
	
	
	
};