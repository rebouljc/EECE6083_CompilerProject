#pragma once
#include "ParseTreeNode.h"

class VariableDeclaration : public ParseTreeNode
{
public:
	VariableDeclaration() {};
	VariableDeclaration(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr);
	void setIsValid(bool isValid) override { this->isValid = isValid; };
	bool getIsValid() override { return this->isValid; };
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	void checkArrayIndexIsIntegerLiteral(ParseTreeNode* numberNode);
	void generateIntermediateCodeFromParseTree(ofstream* outputFileStream, vector<ParseTreeNode*>* declSymbolTablePtr) override;

	//flags for Intermediate-CodeGeneration
	void setglobalVariableSetFlag() { this->globalVariableSetFlag = true; };
	bool getglobalVariableSetFlag() { return this->globalVariableSetFlag; };
	void setLocalVariableSetFlag() { this->localVariableSetFlag = true; };
	bool getLocalVariableSetFlag() { return this->localVariableSetFlag; };

	void setVariableParentIsParameterFlag() { this->variableParentIsParameterFlag = true; };
	bool getVariableParentIsParameterFlag() { return this->variableParentIsParameterFlag; };
	
	~VariableDeclaration(){};
	
	
private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	
	ParseTreeNode* getNodePtr() override;
	bool isValid = false;
	bool globalVariableSetFlag = false;
	bool localVariableSetFlag = false;
	bool variableParentIsParameterFlag = false;
};