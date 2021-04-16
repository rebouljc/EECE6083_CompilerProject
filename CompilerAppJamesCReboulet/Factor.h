#pragma once
#include "ParseTreeNode.h"
class Factor : public ParseTreeNode
{
public:
	Factor(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr);
	void setIsValid(bool isValid) override { this->isValid = isValid; };
	bool getIsValid() override { return this->isValid; };
	void populateSearchResultsList(ParseTreeNode* motherNode) override;

	void generateIntermediateCodeFromParseTree(ofstream* outputFileStream, vector<ParseTreeNode*>* declSymbolTablePtr) override;
	~Factor() {};


private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	void dealWithExpression(ParseTreeNode* motherNode, int tokenCounter);
	ParseTreeNode* getNodePtr() override;
	bool isValid = false;



};