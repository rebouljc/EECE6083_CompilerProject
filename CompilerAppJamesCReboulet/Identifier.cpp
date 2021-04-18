#include "Identifier.h"
#include "VariableDeclaration.h"
#include "ProcedureHeader.h"


Identifier::Identifier()
{

}
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
void Identifier::setStringTypeForIntermediateCodeGeneration(ofstream* outputFileStream)
{
	if (this->typeMarkString == "integer")
	{
		(*outputFileStream) << "i32 ";
	}

	else if (this->typeMarkString == "float")
	{
		(*outputFileStream) << "float ";
	}

	else if (this->typeMarkString == "bool")
	{
		(*outputFileStream) << "i32 ";
	}

	else if (this->typeMarkString == "string")
	{
		(*outputFileStream) << "string ";
	}
}
void Identifier::generateIntermediateCodeFromParseTree(ofstream* outputFileStream, vector<ParseTreeNode*>* declSymbolTablePtr)
{
	VariableDeclaration* varDecl = nullptr;
	ProcedureHeader* procHead = nullptr;
	

	if (!outputFileStream->is_open())
	{
		outputFileStream->open(this->getNodeTokenValue() + ".output");
	}

	else if ((varDecl = dynamic_cast<VariableDeclaration*>(this->parentNodePtr)) != nullptr)
	{
		//Check the global and local symbol tables.
		//Check local first.
		
		
		ParseTreeNode* returnSymbol = nullptr;
		

		if (varDecl->getVariableParentIsParameterFlag())
		{
			this->setStringTypeForIntermediateCodeGeneration(outputFileStream);
		}
		if (declSymbolTablePtr != nullptr && this->searchLocalSymbolTable(this, returnSymbol, declSymbolTablePtr))
		{
			
			(*outputFileStream) << "%";
			
			varDecl->setLocalVariableSetFlag();

			
		}
		
		else if (this->searchLocalSymbolTable(this, returnSymbol, this->programNode_motherNode->getSymbolTable()))
		{
			
			(*outputFileStream) << "@";
			varDecl->setglobalVariableSetFlag();
			
			
			
		}

		(*outputFileStream) << this->getNodeTokenValue();

	}

	else if ((procHead = dynamic_cast<ProcedureHeader*>(this->parentNodePtr)) != nullptr)
	{
		//Check the global and local symbol tables.
		//Check local first.


		ParseTreeNode* returnSymbol = nullptr;

		(*outputFileStream) << " ";

		this->setStringTypeForIntermediateCodeGeneration(outputFileStream);

		if (declSymbolTablePtr != nullptr && this->searchLocalSymbolTable(this, returnSymbol, declSymbolTablePtr))
		{
			(*outputFileStream) << " %";
			procHead->setLocalVariableSetFlag();
		}

		else if (this->searchLocalSymbolTable(this, returnSymbol, this->programNode_motherNode->getSymbolTable()))
		{
			(*outputFileStream) << " @";
			procHead->setglobalVariableSetFlag();
		}

		(*outputFileStream) << this->getNodeTokenValue();
	}

	else if (this->ICGenerationClimbTreeAndCheckForReturnStatement())
	{
		
			this->setStringTypeForIntermediateCodeGeneration(outputFileStream);
			ParseTreeNode* returnSymbol = nullptr;

			if (declSymbolTablePtr != nullptr && this->searchLocalSymbolTable(this, returnSymbol, declSymbolTablePtr))
			{
				(*outputFileStream) << " %";
				
			}

			else if (this->searchLocalSymbolTable(this, returnSymbol, this->programNode_motherNode->getSymbolTable()))
			{
				(*outputFileStream) << " @";
				
			}
			(*outputFileStream) << this->getNodeTokenValue() << "\n";
			
		
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





