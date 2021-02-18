#pragma once
#include "ParseTreeNode.h"
class VariableDeclaration : public ParseTreeNode
{
public:
	VariableDeclaration() {};
	VariableDeclaration(Parser* parser, ParseTreeNode* motherNode);
	void setIsValid(bool isValid) override { this->isValid = isValid; }; //I am too lazy to add these functions to the .cpp file.
	bool getIsValid() override { return this->isValid; };
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	~VariableDeclaration(){};

private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	vector<ParseTreeNode*> linkedMemberNonterminals;
	ParseTreeNode* getNodePtr() override;
	bool isValid = false;
	friend class Parameter;  //We just have to make these guys friends and then they can access the private methods.
};