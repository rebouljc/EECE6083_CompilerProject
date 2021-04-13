#pragma once
#include "ParseTreeNode.h"
class Term : public ParseTreeNode
{
public:
	Term(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr);
	void setIsValid(bool isValid) override { this->isValid = isValid; };
	bool getIsValid() override { return this->isValid; };
	void populateSearchResultsList(ParseTreeNode* motherNode) override;

	//Semantic Arithmetic-Checking methods.
	void setIdentifierTermPtrValue(ParseTreeNode* identifier);
	void setIdentifierTerm_PtrValue(ParseTreeNode* identifier);
	void setNumberTermPtrValue(ParseTreeNode* numberToken);
	void setNumberTerm_PtrValue(ParseTreeNode* numberToken);

	ParseTreeNode* getIdentifierTermPtrValue();
	ParseTreeNode* getIdentifierTerm_PtrValue();
	ParseTreeNode* getNumberTermPtrValue();
	ParseTreeNode* getNumberTerm_PtrValue();
	
	~Term() {};

private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	
	ParseTreeNode* getNodePtr() override;
	bool isValid = false;
	ParseTreeNode* identifierArithOpPtr = nullptr;
	ParseTreeNode* identifierArithOp_Ptr = nullptr;


};