#pragma once
#include "ParseTreeNode.h"
class ProcedureHeader : public ParseTreeNode
{
public:
	ProcedureHeader(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr);
	void setIsValid(bool isValid) override { this->isValid = isValid; };
	bool getIsValid() override { return this->isValid; };
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	unsigned int getLinkedMemberNonterminalsSize();

	void generateIntermediateCodeFromParseTree(ofstream* outputFileStream, vector<ParseTreeNode*>* declSymbolTablePtr) override;
	
	~ProcedureHeader() {};

private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	
	ParseTreeNode* getNodePtr() override;
	bool isValid = false;

};