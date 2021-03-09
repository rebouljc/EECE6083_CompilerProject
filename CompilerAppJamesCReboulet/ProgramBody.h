#pragma once
#include "ParseTreeNode.h"

class ProgramBody : public ParseTreeNode
{
public:
	ProgramBody(Parser* parser, ParseTreeNode* motherNode);
	~ProgramBody() {};
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	void populateLocalSearchResultsList() override;

private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	void verifySyntaxCreateParseTreeDeclarationParser(ParseTreeNode* motherNode);
	void verifySyntaxCreateParseTreeStatementParser(ParseTreeNode* motherNode);
	vector<ParseTreeNode*> linkedMemberNonterminals;
	ParseTreeNode* getNodePtr() override;
	

};