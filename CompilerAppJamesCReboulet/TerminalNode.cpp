#include "TerminalNode.h"
#include "TypeMark.h"
#include "VariableDeclaration.h"
#include "ProcedureHeader.h"
#include "ProgramBody.h"
#include "IfStatement.h"




TerminalNode::TerminalNode()
{
	this->token = nullptr;
}

TerminalNode::TerminalNode(Token* token, ParseTreeNode* parentNodePtr, ParseTreeNode* motherNodePtr)
{
	//Note: 3-13-2021: Added additional statement to set this node's parent node ptr, to enable reverse walking back up a tree.
	this->parentNodePtr = parentNodePtr;
	this->token = token;
	this->programNode_motherNode = motherNodePtr;
							 
}

void TerminalNode::generateIntermediateCodeFromParseTree(ofstream* outputFileStream, vector<ParseTreeNode*>* declSymbolTablePtr)
{
	TypeMark* typeMark = nullptr;
	VariableDeclaration* varDecl = nullptr;
	IfStatement* ifStmt = nullptr;
	

	if (dynamic_cast<TypeMark*>(this->parentNodePtr) != nullptr && 
		(varDecl = dynamic_cast<VariableDeclaration*>(this->parentNodePtr->getParentNodePtr())) != nullptr &&
		 !varDecl->getVariableParentIsParameterFlag()
	   )
	{
		if (this->getNodeTokenValue() == "integer")
		{
			
			(*outputFileStream) << " i32\n";
		
		}

		else if (this->getNodeTokenValue() == "float")
		{
			(*outputFileStream) << " float\n";
		}

		else if (this->getNodeTokenValue() == "string")
		{
			(*outputFileStream) << " string\n";
		}

		else if (this->getNodeTokenValue() == "bool")
		{
			(*outputFileStream) << " i32\n";
		}

		
	}

	
	else if ((varDecl = dynamic_cast<VariableDeclaration*>(this->parentNodePtr)) != nullptr &&
		      !varDecl->getVariableParentIsParameterFlag()
		    )
	{		
		if (this->getNodeTokenValue() == ":")
		{
			(*outputFileStream) << "=";
		}
		if (varDecl->getglobalVariableSetFlag())
		{
			(*outputFileStream) << " global";
		}

		else if(varDecl->getLocalVariableSetFlag())
		{
			(*outputFileStream) << " alloca";
		}

		
	}

	else if (dynamic_cast<ProcedureHeader*>(this->parentNodePtr) != nullptr)
	{
		if (this->getNodeTokenValue() == "procedure")
		{
			(*outputFileStream) << "define";
		}

		else if (this->getNodeTokenValue() == "(")
		{
			(*outputFileStream) << "(";
		}

		else if (this->getNodeTokenValue() == ")")
		{
			(*outputFileStream) << ")";
		}

		
	}
	else if (dynamic_cast<ProgramBody*>(this->parentNodePtr) != nullptr)
	{
		if (this->getNodeTokenValue() == "begin")
		{
			(*outputFileStream) << "define i32 @main() {\n";
		}
		else if (this->getNodeTokenValue() == "program")
		{
			(*outputFileStream) << "}\n";
		}
	}

	else if ((ifStmt = dynamic_cast<IfStatement*>(this->parentNodePtr)) != nullptr)
	{
		int index = this->ICCodeGenerationClimbTreeToProcedureBodyAndGetIndexValue();
		
		if (this->getNodeTokenValue() == "then")
		{
			
			(*outputFileStream) << "\nbtrue" << index << ":\n";
		}

		else if (this->getNodeTokenValue() == "else")
		{
			(*outputFileStream) << "\nbfalse" << index << ":\n";
		}

		else if (this->getNodeTokenValue() == "end")
		{   
			
			(*outputFileStream) << "br label %end" << index << "\n";
			(*outputFileStream) << "bfalse" << index << ":\n";
			(*outputFileStream) << "br label %end" << index << "\n";
			(*outputFileStream) << "\nend" << index << ":\n";
 			this->ICCodeGenerationClimbTreeToProcedureBodyAndIncrementIndexValue();
		}
	}

	else if (this->getNodeTokenValue() == "return")
	{
		(*outputFileStream) << "ret";
	}

	else if (this->getNodeTokenValue() == "==")
	{
		(*outputFileStream) << " oeq float";
	}

	else if (this->getNodeTokenValue() == "!=")
	{
		(*outputFileStream) << " one float";
	}

	else if (this->getNodeTokenValue() == "<")
	{
		(*outputFileStream) << " olt float";
	}

	else if (this->getNodeTokenValue() == "<=")
	{
		(*outputFileStream) << " ole float";
	}

	else if (this->getNodeTokenValue() == ">")
	{
		(*outputFileStream) << " ogt float";
	}

	else if (this->getNodeTokenValue() == ">=")
	{
		(*outputFileStream) << " oge float";
	}

	
	

	



	


}

//Now, we will add a couple of duplicate methods from Token* here to streamline the process.  There are a lot of unnecessary public methods in token 
//that are not needed here and may make things confusing.

string TerminalNode::getNodeTokenType()
{
	return this->token->getTokenType();
}
string TerminalNode::getNodeTokenValue()
{
	return this->token->getTokenValue();
}

void TerminalNode::setNodeTokenValue(std::string value)
{
	this->token->setTokenValue(value);
}

void TerminalNode::setNodeTokenType(std::string type)
{
	this->token->setTokenType(type);
}

int TerminalNode::getNodeTokenLineNumber()
{
	return this->token->getTokenLineNumber();
}

ParseTreeNode* TerminalNode::getNodePtr()
{
	return this;

}

void TerminalNode::populateSearchResultsList(ParseTreeNode* motherNode)
{
	motherNode->addToSearchResultsList(this->getNodePtr());
}




