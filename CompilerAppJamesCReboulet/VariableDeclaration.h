#pragma once
#include "ParseTreeNode.h"
class VariableDeclaration : public ParseTreeNode
{
public:
	VariableDeclaration(Parser* parser, ParseTreeNode* motherNode);
	void setIsValid(bool isValid) { this->isValid = isValid; }; //I am too lazy to add these functions to the .cpp file.
	bool getIsValid() { return this->isValid; };
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	~VariableDeclaration(){};

private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	vector<ParseTreeNode*> linkedMemberNonterminals;
	ParseTreeNode* getNodePtr() override;
	bool isValid = false;

};