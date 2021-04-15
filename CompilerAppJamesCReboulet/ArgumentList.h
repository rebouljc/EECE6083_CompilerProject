#pragma once
#include "ParseTreeNode.h"
class ArgumentList : public ParseTreeNode
{
public:
	ArgumentList(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr);
	void setIsValid(bool isValid) override { this->isValid = isValid; };
	bool getIsValid() override { return this->isValid; };
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	void generateIntermediateCodeFromParseTree(ofstream* outputFileStream) override;
	
	~ArgumentList() {};
	


private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	
	ParseTreeNode* getNodePtr() override;
	bool isValid = false;


};