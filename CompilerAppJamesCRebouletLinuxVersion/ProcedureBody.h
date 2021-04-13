#pragma once
#include "ParseTreeNode.h"
class ProcedureBody : public ParseTreeNode
{
public:
	ProcedureBody(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr);
	void setIsValid(bool isValid) override { this->isValid = isValid; };
	bool getIsValid() override { return this->isValid; };
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	
	~ProcedureBody() {};

private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	void verifySyntaxCreateParseTreeDeclarationParser(ParseTreeNode* motherNode);
	void verifySyntaxCreateParseTreeStatementParser(ParseTreeNode* motherNode);
	
	ParseTreeNode* getNodePtr() override;
	bool isValid = false;
	

};