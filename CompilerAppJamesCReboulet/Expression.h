#pragma once
#include "ParseTreeNode.h"

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

	~Expression() {};
	

private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	
	ParseTreeNode* getNodePtr() override;
	bool isValid = false;

	//These are really pointers to the identifiers in Term and Term_.  I was too lazy to rename them.
	//They work as they are, and I don't want to risk potentially messing them up by renaming them.

	ParseTreeNode* identifierArithOpPtr = nullptr;
	ParseTreeNode* identifierArithOp_Ptr = nullptr;
	
	


};