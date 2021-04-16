#include "Identifier.h"


Identifier::Identifier(Token* token, ParseTreeNode* motherNode, string identifierType, ParseTreeNode* parentNodePtr)
{
	//Note: 3-13-2021: Added additional statement to set this node's parent node ptr, to enable reverse walking back up a tree.
	this->parentNodePtr = parentNodePtr;
	this->token = token;
	this->programNode_motherNode = motherNode;
	this->identifierType = identifierType;
	this->climbTreeAndPopulateSymbolTable(this->identifierType, this);
	
	//Semantic Check
	//1) We need to climb the parse tree until we get to <ArithOp_>. We add a pointer to <ArithOp_> to the identifier.
	//2) We then continue to climb the tree until we get to <ArithOp>.  We add a pointer to <ArithOp> to the identifier.
	//3) We then need to continue to climb the tree until we get to a <Declaration>.
	//4) Once we arrive at <Declaration>.  We search for a matching identifier node.
	//5) We then verify its type.  If it is of type "integer" or type "float", we then search <ArithOp_> to verify that
	
	this->climbTreeAndVerifyArithmeticOperationsAreCorrectlyDefined(this, false);

	this->climbTreeAndVerifyTermOperationsAreCorrectlyDefined(this, false);

	bool relationPresentFlag = false;
	bool setRelationPresentFlag = false;
	this->climbTreeAndVerifyRelationOperationsAreCorrectlyDefined(this, false, relationPresentFlag, setRelationPresentFlag);

	bool expressionDefinedFlag = false;
	bool notWithParenthesesFlag = false;
	bool singleVariableIfLoopExpressionPresent = false;
	this->climbTreeAndVerifyExpressionOperationsAreCorrectlyDefined(this, false, expressionDefinedFlag, singleVariableIfLoopExpressionPresent);
	
	

}

void Identifier::generateIntermediateCodeFromParseTree(ofstream* outputFileStream, vector<ParseTreeNode*>* declSymbolTablePtr)
{
	if (!outputFileStream->is_open())
	{
		outputFileStream->open(this->getNodeTokenValue() + ".output");
	}

	else
	{
		(*outputFileStream) << this->getNodeTokenValue();
		
		
	}
}



Identifier::Identifier(Token* token, ParseTreeNode* motherNode, string identifierType, ParseTreeNode* parentNodePtr, bool isValidDeclaration)
{
	//Note: 3-13-2021: Added additional statement to set this node's parent node ptr, to enable reverse walking back up a tree.
	this->parentNodePtr = parentNodePtr;
	this->token = token;
	this->programNode_motherNode = motherNode;
	this->identifierType = identifierType;
	this->isValidDeclaration = isValidDeclaration;
	this->climbTreeAndPopulateSymbolTable(this->identifierType, this);
	
}

void Identifier::setIdentifierTypeToGlobal()
{
	this->identifierType = "GLOBAL";
}

//Now, we will add a couple of duplicate methods from Token* here to streamline the process.  There are a lot of unnecessary public methods in token 
//that are not needed here and may make things confusing.

string Identifier::getNodeSymbolIdentifierType()
{
	return this->identifierType;
}

ParseTreeNode* Identifier::getNodePtr()
{
	return this;

}

void Identifier::populateSearchResultsList(ParseTreeNode* motherNode)
{
	motherNode->addToSearchResultsList(this->getNodePtr());
}

void Identifier::setNumberPtrValue(ParseTreeNode* numberNode)
{
	this->numberPtr = numberNode;
}

ParseTreeNode* Identifier::getNumberPtrValue()
{
	return this->numberPtr;
}





