#pragma once
#include "ParseTreeNode.h"

class Program: public ParseTreeNode
{
public:
	Program(Parser* parser);
	
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	
	~Program() {};
	
	
private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	
	ParseTreeNode* getNodePtr() override;
	

};