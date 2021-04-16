#include "StringLiteral.h"

StringLiteral::StringLiteral(Token* token, ParseTreeNode* parentNodePtr)
{
	//Note: 3-13-2021: Added additional statement to set this node's parent node ptr, to enable reverse walking back up a tree.
	this->parentNodePtr = parentNodePtr;
	this->token = token;

	bool relationPresentFlag = false;
	bool setRelationPresentFlag = true;
	this->climbTreeAndVerifyRelationOperationsAreCorrectlyDefined(this, false, relationPresentFlag, setRelationPresentFlag);
	bool expressionDefinedFlag = false;
	bool singleVariableIfLoopExpressionPresent = false;
	
	this->climbTreeAndVerifyExpressionOperationsAreCorrectlyDefined(this, false, expressionDefinedFlag, singleVariableIfLoopExpressionPresent);

}

void StringLiteral::generateIntermediateCodeFromParseTree(ofstream* outputFileStream, vector<ParseTreeNode*>* declSymbolTablePtr)
{

}

ParseTreeNode* StringLiteral::getNodePtr()
{
	return this;

}

void StringLiteral::populateSearchResultsList(ParseTreeNode* motherNode)
{
	motherNode->addToSearchResultsList(this->getNodePtr());
}
