#pragma once
#include "ParseTreeNode.h"

class VariableDeclaration : public ParseTreeNode
{
public:
	VariableDeclaration() {};
	VariableDeclaration(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr);
	void setIsValid(bool isValid) override { this->isValid = isValid; }; //I am too lazy to add these functions to the .cpp file.
	bool getIsValid() override { return this->isValid; };
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	void checkArrayIndexIsIntegerLiteral(ParseTreeNode* numberNode);
	void generateIntermediateCodeFromParseTree(ofstream* outputFileStream, vector<ParseTreeNode*>* declSymbolTablePtr) override;
	
	
	
	~VariableDeclaration(){};
	
	
private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	
	ParseTreeNode* getNodePtr() override;
	bool isValid = false;
};