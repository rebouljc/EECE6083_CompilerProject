#pragma once
#include "ParseTreeNode.h"
#include "Identifier.h"


class Declaration : public ParseTreeNode
{
public:
	Declaration(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr);
	void setIsValid(bool isValid) override { this->isValid = isValid; };
	bool getIsValid() override { return this->isValid; };
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	void verifyArithmeticOperationsAreCorrectlyDefined(Identifier* tokenToCompareLeft, Identifier* tokenToCompareRight,
		                                               Identifier* prevTokenToCompareLeft, Identifier* prevTokenToCompareRight);
	
	~Declaration() {};
	bool checkGlobalTerminalNodePresent() override;


private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	void verifyArithmeticOperationsAreCorrectlyDefinedPostDeclaration(ParseTreeNode* tokenToCompareLeft, ParseTreeNode* tokenToCompareRight);
	ParseTreeNode* getNodePtr() override;
	bool isValid = false;
	//ParseTreeNode* tokenToCompareLeft = nullptr;
	//ParseTreeNode* tokenToCompareRight = nullptr;
	
	
	
	
};