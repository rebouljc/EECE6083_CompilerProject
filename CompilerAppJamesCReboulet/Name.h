#pragma once
#include "ParseTreeNode.h"
class Name : public ParseTreeNode
{
public:
	Name(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr);
	void setIsValid(bool isValid) override { this->isValid = isValid; };
	bool getIsValid() override { return this->isValid; };
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	void checkArrayIndexIsIntegerLiteral(ParseTreeNode* numberNode);

	void generateIntermediateCodeFromParseTree(ofstream* outputFileStream, vector<ParseTreeNode*>* declSymbolTablePtr) override;
	
	~Name() {};

private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	
	ParseTreeNode* getNodePtr() override;
	bool isValid = false;
	
	//Semantic checking methods.

	bool checkIdentifierFollowsScopingRules();


};