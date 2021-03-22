#pragma once
#include "ParseTreeNode.h"
class Bound : public ParseTreeNode
{
public:
	Bound(Token* token, Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr);
	void setIsValid(bool isValid) override { this->isValid = isValid; };
	bool getIsValid() override { return this->isValid; };
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	~Bound() {};

	//Semantic checking methods.
	vector<ParseTreeNode*>& getLinkedMemberNonterminalsList();
	void checkArrayIndexWithinRange(ParseTreeNode numberNode);
	

private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	vector<ParseTreeNode*> linkedMemberNonterminals;
	ParseTreeNode* getNodePtr() override;
	bool isValid = false;
	Token* token;

	


};