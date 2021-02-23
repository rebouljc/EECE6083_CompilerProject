#pragma once
#include "ParseTreeNode.h"
class ProcedureCall : public ParseTreeNode
{
public:
	ProcedureCall(Parser* parser, ParseTreeNode* motherNode);
	void setIsValid(bool isValid) override { this->isValid = isValid; };
	bool getIsValid() override { return this->isValid; };
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	~ProcedureCall() {};

private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	void createEnumList(ParseTreeNode* motherNode);
	vector<ParseTreeNode*> linkedMemberNonterminals;
	ParseTreeNode* getNodePtr() override;
	bool isValid = false;


};