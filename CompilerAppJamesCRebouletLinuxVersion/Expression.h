#pragma once
#include "ParseTreeNode.h"
#include "StringLiteral.h"

class Expression : public ParseTreeNode
{
public:
	Expression(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr);
	void setIsValid(bool isValid) override { this->isValid = isValid; };
	bool getIsValid() override { return this->isValid; };
	void populateSearchResultsList(ParseTreeNode* motherNode) override;

	//Semantic Arithmetic-Checking methods.
	void setIdentifierExpressionPtrValue(ParseTreeNode* identifier);
	void setIdentifierExpression_PtrValue(ParseTreeNode* identifier);
	void setNumberExpressionPtrValue(ParseTreeNode* numberToken);
	void setNumberExpression_PtrValue(ParseTreeNode* numberToken);

	ParseTreeNode* getIdentifierExpressionPtrValue();
	ParseTreeNode* getIdentifierExpression_PtrValue();
	ParseTreeNode* getNumberExpressionPtrValue();
	ParseTreeNode* getNumberExpression_PtrValue();

	//Setters and getters for string literals.
	void setStringLiteralExpressionPtrValue(ParseTreeNode* stringLiteral);
	void setStringLiteralExpression_PtrValue(ParseTreeNode* stringLiteral);
	ParseTreeNode* getStringLiteralExpressionPtrValue();
	ParseTreeNode* getStringLiteralExpression_PtrValue();

	//Parentheses Set Flag setter and getter
	void setParenthesesPresentFlag(bool flagValue) { this->parenthesesSetFlag = flagValue; };
	bool getParenthesesPresentFlag() { return this->parenthesesSetFlag; };
	void setNotPresentFlag(bool flagValue) { this->notSetFlag = flagValue; };
	bool getNotPresentFlag() { return this->notSetFlag; };
	void setIfLoopStatementPresentFlag(bool flagValue) { this->ifLoopStatementPresentFlag = flagValue; };
	bool getIfLoopStatementPresentFlag() { return this->ifLoopStatementPresentFlag; };
	void setSingleVariableIfLoopExpressionFlag(bool flagValue) { this->singleVariableIfOrLoopExpressionFlag = flagValue; };
	bool getSingleVariableIfLoopExpressionFlag() { return this->singleVariableIfOrLoopExpressionFlag; };
	
	~Expression() {};
	

private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	
	ParseTreeNode* getNodePtr() override;
	bool isValid = false;

	//These are really pointers to the identifiers in Term and Term_.  I was too lazy to rename them.
	//They work as they are, and I don't want to risk potentially messing them up by renaming them.

	ParseTreeNode* identifierArithOpPtr = nullptr;
	ParseTreeNode* identifierArithOp_Ptr = nullptr;
	bool parenthesesSetFlag = false;
	bool notSetFlag = false;
	bool ifLoopStatementPresentFlag = false;
	bool singleVariableIfOrLoopExpressionFlag = false;
	
	


};