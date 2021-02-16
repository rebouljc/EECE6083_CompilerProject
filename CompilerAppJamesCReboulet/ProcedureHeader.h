#pragma once
#include "ParseTreeNode.h"
class ProcedureHeader : public ParseTreeNode
{
public:
	ProcedureHeader(Parser* parser, ParseTreeNode* motherNode);
	void setIsValid(bool isValid) { this->isValid = isValid; };
	bool getIsValid() { return this->isValid; };
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	~ProcedureHeader() {};

private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	vector<ParseTreeNode*> linkedMemberNonterminals;
	ParseTreeNode* getNodePtr() override;
	bool isValid = false;

};