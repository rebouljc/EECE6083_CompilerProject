#pragma once
#include "ParseTreeNode.h"
class ArithOp : public ParseTreeNode
{
public:
	ArithOp(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr);
	void setIsValid(bool isValid) override { this->isValid = isValid; };
	bool getIsValid() override { return this->isValid; };
	void populateSearchResultsList(ParseTreeNode* motherNode) override;

	//Semantic Arithmetic-Checking methods.
	void setIdentifierArithOpPtrValue(ParseTreeNode* identifier);
	void setIdentifierArithOp_PtrValue(ParseTreeNode* identifier);
	void setNumberArithOpPtrValue(ParseTreeNode* numberToken);
	void setNumberArithOp_PtrValue(ParseTreeNode* numberToken);
	
	ParseTreeNode* getIdentifierArithOpPtrValue();
	ParseTreeNode* getIdentifierArithOp_PtrValue();
	ParseTreeNode* getNumberArithOpPtrValue();
	ParseTreeNode* getNumberArithOp_PtrValue();

	void generateIntermediateCodeFromParseTree(ifstream* outputFileStream) override;
	~ArithOp() {};


private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;

	ParseTreeNode* getNodePtr() override;
	bool isValid = false;
	ParseTreeNode* identifierArithOpPtr = nullptr;
	ParseTreeNode* identifierArithOp_Ptr = nullptr;
	
	

};