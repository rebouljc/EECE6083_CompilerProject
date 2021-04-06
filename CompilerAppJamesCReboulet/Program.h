#pragma once
#include "ParseTreeNode.h"
#include "Identifier.h"
#include "Number.h"
#include "StringLiteral.h"

class Program: public ParseTreeNode
{
public:
	Program(Parser* parser);
	
	void populateSearchResultsList(ParseTreeNode* motherNode) override;

	//Semantic Analysis Public Methods
	void verifyArithmeticOperationsAreCorrectlyDefined(Identifier* tokenToCompareLeft, Identifier* tokenToCompareRight, 
		                                               bool& leftTokInserted, bool& rightTokInserted);
	void verifyArithmeticOperationsAreCorrectlyDefinedNumberLeft(Number* tokenToCompareLeft, Identifier* tokenToCompareRight,
		                                                         bool& leftTokInserted, bool& rightTokInserted);
	void verifyArithmeticOperationsAreCorrectlyDefinedNumberRight(Identifier* tokenToCompareLeft, Number* tokenToCompareRight,
		                                                          bool& leftTokInserted, bool& rightTokInserted);
	void verifyArithmeticOperationsAreCorrectlyDefinedStringLiteralLeft(StringLiteral* tokenToCompareLeft, Identifier* tokenToCompareRight,
		                                                                bool& leftTokInserted, bool& rightTokInserted);
	void verifyArithmeticOperationsAreCorrectlyDefinedStringLiteralRight(Identifier* tokenToCompareLeft, StringLiteral* tokenToCompareRight,
		bool& leftTokInserted, bool& rightTokInserted);

	
	
	~Program() {};
	
	
private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;

	//Semantic Analysis Private Methods
	void verifyArithmeticOperationsAreCorrectlyDefinedPostDeclaration(ParseTreeNode* tokenToCompareLeft, ParseTreeNode* tokenToCompareRight);
	void verifyExpressionOperationsAreCorrectlyDefinedPostDeclaration(ParseTreeNode* tokenToCompareLeft, ParseTreeNode* tokenToCompareRight, bool& relationSet);
	ParseTreeNode* getNodePtr() override;
	
};