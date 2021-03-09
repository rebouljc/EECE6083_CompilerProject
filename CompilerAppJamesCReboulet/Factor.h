#pragma once
#include "ParseTreeNode.h"
class Factor : public ParseTreeNode
{
public:
	Factor(Parser* parser, ParseTreeNode* motherNode);
	void setIsValid(bool isValid) override { this->isValid = isValid; };
	bool getIsValid() override { return this->isValid; };
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	void populateLocalSearchResultsList() override;
	~Factor() {};

private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	void dealWithExpression(ParseTreeNode* motherNode, int tokenCounter);
	vector<ParseTreeNode*> linkedMemberNonterminals;
	ParseTreeNode* getNodePtr() override;
	bool isValid = false;


};