#pragma once
#include "ParseTreeNode.h"
#include "Identifier.h"
class Destination : public ParseTreeNode
{
public:
	Destination(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr);
	void setIsValid(bool isValid) override { this->isValid = isValid; };
	bool getIsValid() override { return this->isValid; };
	void populateSearchResultsList(ParseTreeNode* motherNode) override;
	void generateIntermediateCodeFromParseTree(ofstream* outputFileStream, vector<ParseTreeNode*>* declSymbolTablePtr) override;
	~Destination() {};
	
	
	//Semantic Checking Methods
	void checkArrayIndexIsIntegerLiteral(ParseTreeNode* numberNode);
	


private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	//Semantic-Checking Method.  Private.

	
	ParseTreeNode* getNodePtr() override;
	bool isValid = false;

	//Semantic checking methods.

	bool checkIdentifierFollowsScopingRules();

	


};