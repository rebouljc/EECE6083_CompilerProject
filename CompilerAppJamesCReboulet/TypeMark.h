#pragma once
#include "ParseTreeNode.h"
class TypeMark : public ParseTreeNode
{
public:
	TypeMark(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr);
	void setIsValid(bool isValid) override { this->isValid = isValid; };
	bool getIsValid() override { return this->isValid; };
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	
	void generateIntermediateCodeFromParseTree(ifstream* outputFileStream) override;
	
	~TypeMark() {};

private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	void createEnumList(ParseTreeNode* motherNode);
	
	ParseTreeNode* getNodePtr() override;
	bool isValid = false;


};