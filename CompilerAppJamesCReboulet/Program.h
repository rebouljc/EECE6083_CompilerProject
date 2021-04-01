#pragma once
#include "ParseTreeNode.h"
#include "Identifier.h"
#include "Number.h"

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
	
	~Program() {};
	
	
private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;

	//Semantic Analysis Private Methods
	void verifyArithmeticOperationsAreCorrectlyDefinedPostDeclaration(ParseTreeNode* tokenToCompareLeft, ParseTreeNode* tokenToCompareRight);
	ParseTreeNode* getNodePtr() override;
	
};