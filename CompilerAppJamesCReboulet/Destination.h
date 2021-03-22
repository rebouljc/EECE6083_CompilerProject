#pragma once
#include "ParseTreeNode.h"
class Destination : public ParseTreeNode
{
public:
	Destination(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr);
	void setIsValid(bool isValid) override { this->isValid = isValid; };
	bool getIsValid() override { return this->isValid; };
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	~Destination() {};
	
	//Get linkedNonterminals for semantic check
	vector<ParseTreeNode*>& getLinkedMemberNonterminalsList();
	//Semantic Checking Methods
	void checkArrayIndexIsIntegerLiteral(ParseTreeNode* numberNode);
	


private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	vector<ParseTreeNode*> linkedMemberNonterminals;
	ParseTreeNode* getNodePtr() override;
	bool isValid = false;

	//Semantic checking methods.

	bool checkIdentifierFollowsScopingRules();

	


};