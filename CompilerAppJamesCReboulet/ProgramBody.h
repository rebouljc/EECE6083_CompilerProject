#pragma once
#include "ParseTreeNode.h"

class ProgramBody : public ParseTreeNode
{
public:
	ProgramBody(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr);
	
	~ProgramBody() {};
	void populateSearchResultsList(ParseTreeNode* motherNode) override;

	void generateIntermediateCodeFromParseTree(ifstream* outputFileStream) override;

private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	void verifySyntaxCreateParseTreeDeclarationParser(ParseTreeNode* motherNode);
	void verifySyntaxCreateParseTreeStatementParser(ParseTreeNode* motherNode);
	
	ParseTreeNode* getNodePtr() override;
	

};