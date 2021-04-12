#pragma once
#include "ParseTreeNode.h"
#include "Identifier.h"
#include "Number.h"
#include "StringLiteral.h"


class Declaration : public ParseTreeNode
{
public:
	Declaration(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr);
	void setIsValid(bool isValid) override { this->isValid = isValid; };
	bool getIsValid() override { return this->isValid; };
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
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
	void verifyStringOperationsAreCorrectlyDefined(Identifier* tokenToCompareLeftIdentifier, 
		                                           StringLiteral* tokenToCompareLeftStringLiteral,
		                                           Number* tokenToCompareLeftNumber
	                                              );
	~Declaration() {};
	bool checkGlobalTerminalNodePresent() override;
	


private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	void verifyArithmeticOperationsAreCorrectlyDefinedPostDeclaration(ParseTreeNode* tokenToCompareLeft, ParseTreeNode* tokenToCompareRight);
	void verifyExpressionOperationsAreCorrectlyDefinedPostDeclaration(ParseTreeNode* tokenToCompareLeft, ParseTreeNode* tokenToCompareRight, bool &relationSet);
	ParseTreeNode* getNodePtr() override;
	bool isValid = false;
	
	//ParseTreeNode* tokenToCompareLeft = nullptr;
	//ParseTreeNode* tokenToCompareRight = nullptr;
	
	
	
	
};