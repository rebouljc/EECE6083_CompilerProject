#pragma once
#include "ParseTreeNode.h"
class ProcedureDeclaration : public ParseTreeNode
{
public:
	ProcedureDeclaration(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr);
	void setIsValid(bool isValid) override { this->isValid = isValid; };
	bool getIsValid() override { return this->isValid; };
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	
	~ProcedureDeclaration() {};

private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;

	ParseTreeNode* getNodePtr() override;
	bool isValid = false;
	

};