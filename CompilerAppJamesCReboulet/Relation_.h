#pragma once
#include "ParseTreeNode.h"
class Relation_: public ParseTreeNode
{
public:
	Relation_(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr);
	void setIsValid(bool isValid) override { this->isValid = isValid; };
	bool getIsValid() override { return this->isValid; };
	void populateSearchResultsList(ParseTreeNode* motherNode) override;

	void generateIntermediateCodeFromParseTree(ifstream* outputFileStream) override;
	
	~Relation_() {};

private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	
	ParseTreeNode* getNodePtr() override;
	bool isValid = false;


};