#pragma once
#include "ParseTreeNode.h"
class ProcedureCall : public ParseTreeNode
{
public:
	ProcedureCall(Parser* parser, ParseTreeNode* motherNode);
	ProcedureCall(Parser* parser, ParseTreeNode* motherNode, Token* stolenToken);
	void setIsValid(bool isValid) override { this->isValid = isValid; };
	bool getIsValid() override { return this->isValid; };
	void setStolenToken(Token* stolenToken) { this->stolenToken = stolenToken; };
	Token* getIsStolenToken() { return this->stolenToken; };
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	void populateLocalSearchResultsList() override;
	~ProcedureCall() {};

private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	vector<ParseTreeNode*> linkedMemberNonterminals;
	ParseTreeNode* getNodePtr() override;
	bool isValid = false;
	Token* stolenToken;

};