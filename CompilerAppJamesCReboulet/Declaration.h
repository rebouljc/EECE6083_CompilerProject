#pragma once
#include "ParseTreeNode.h"

class Declaration : public ParseTreeNode
{
public:
	Declaration(Parser* parser, ParseTreeNode* motherNode);
	void setIsValid(bool isValid) { this->isValid = isValid; };
	bool getIsValid() { return this->isValid; };
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	~Declaration() {};

private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	vector<ParseTreeNode*> linkedMemberNonterminals;
	ParseTreeNode* getNodePtr() override;
	bool isValid = false;
};