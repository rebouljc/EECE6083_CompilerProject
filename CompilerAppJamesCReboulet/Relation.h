#pragma once
#include "ParseTreeNode.h"
class Relation : public ParseTreeNode
{
public:
	Relation(Parser* parser, ParseTreeNode* motherNode, ParseTreeNode* parentNodePtr);
	void setIsValid(bool isValid) override { this->isValid = isValid; };
	bool getIsValid() override { return this->isValid; };
	void populateSearchResultsList(ParseTreeNode* motherNode) override;

	void setIdentifierRelationPtrValue(ParseTreeNode* identifier);
	void setIdentifierRelation_PtrValue(ParseTreeNode* identifier);
	void setNumberRelationPtrValue(ParseTreeNode* numberToken);
	void setNumberRelation_PtrValue(ParseTreeNode* numberToken);
	void setStringLiteralRelationPtrValue(ParseTreeNode* stringLiteral);
	void setStringLiteralRelation_PtrValue(ParseTreeNode* stringLiteral);

	ParseTreeNode* getIdentifierRelationPtrValue();
	ParseTreeNode* getIdentifierRelation_PtrValue();
	ParseTreeNode* getNumberRelationPtrValue();
	ParseTreeNode* getNumberRelation_PtrValue();
	ParseTreeNode* getStringLiteralRelationPtrValue();
	ParseTreeNode* getStringLiteralRelation_PtrValue();

	void generateIntermediateCodeFromParseTree(ifstream* outputFileStream) override;
	~Relation() {};

private:
	void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode) override;
	
	ParseTreeNode* getNodePtr() override;
	bool isValid = false;

	ParseTreeNode* identifierArithOpPtr = nullptr;
	ParseTreeNode* identifierArithOp_Ptr = nullptr;



};