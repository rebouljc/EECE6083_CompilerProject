#pragma once
#include "ParseTreeNode.h"
class ProcedureCall : public ParseTreeNode
{
public:
	ProcedureCall(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr);
	ProcedureCall(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr,Token* stolenToken);
	void setIsValid(bool isValid) override { this->isValid = isValid; };
	bool getIsValid() override { return this->isValid; };
	void setStolenToken(Token* stolenToken) { this->stolenToken = stolenToken; };
	Token* getIsStolenToken() { return this->stolenToken; };
	void populateSearchResultsList(ParseTreeNode* motherNode) override;

	void generateIntermediateCodeFromParseTree(ofstream* outputFileStream) override;
	
	~ProcedureCall() {};

private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	
	ParseTreeNode* getNodePtr() override;
	bool isValid = false;
	Token* stolenToken;

	//Semantic checking methods.

	bool checkIdentifierFollowsScopingRules();

};