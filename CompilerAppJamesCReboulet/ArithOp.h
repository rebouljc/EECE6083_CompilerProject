#pragma once
#include "ParseTreeNode.h"
class ArithOp : public ParseTreeNode
{
public:
	ArithOp(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr);
	void setIsValid(bool isValid) override { this->isValid = isValid; };
	bool getIsValid() override { return this->isValid; };
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	void setIdentifierArithOpPtrValue(ParseTreeNode* identifier);
	void setIdentifierArithOp_PtrValue(ParseTreeNode* identifier);
	ParseTreeNode* getIdentifierArithOpPtrValue();
	ParseTreeNode* getIdentifierArithOp_PtrValue();
	~ArithOp() {};


private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	void dealWithForHeader(ParseTreeNode* motherNode, int tokenCounter);
	void dealWithForBody(ParseTreeNode* motherNode, int tokenCounter);

	//Semantic Analysis Methods
	void climbTreeAndVerifyArithmeticOperationsAreCorrectlyDefined();
	
	ParseTreeNode* getNodePtr() override;
	bool isValid = false;
	ParseTreeNode* identifierArithOpPtr = nullptr;
	ParseTreeNode* identifierArithOp_Ptr = nullptr;
	
	

};