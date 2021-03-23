#pragma once
#include <vector>
#include "Token.h"
#include "Parser.h"

class ParseTreeNode
{
public:
	
	vector<ParseTreeNode*>* getSearchResultsList(ParseTreeNode* currentProgramNodePtr);
	
	void addToSearchResultsList(ParseTreeNode* nodeToAdd);
	bool addToSymbolTable(ParseTreeNode* symbolToAdd, bool checkUnique);
	bool searchSymbolTable(ParseTreeNode* searchSymbol, ParseTreeNode* returnSymbol);
	virtual void populateSearchResultsList(ParseTreeNode* motherNode = nullptr) { return; };
	vector<ParseTreeNode*>* getSymbolTable();
	virtual void setIsValid(bool isValid) {};
	virtual bool getIsValid() { return false; };
	void setParserPtr(Parser* parserPtr);
	virtual ~ParseTreeNode() {};
	virtual bool checkGlobalTerminalNodePresent() { return false; };

	//Tree climbing methods for semantic verification.
	void climbTreeAndPopulateSymbolTable(string identifierType, ParseTreeNode* identifierNode);
	void climbTreeAndVerifyArrayIndices(ParseTreeNode* numberNode);
	void climbTreeAndPerformArrayBoundsCheck(ParseTreeNode* numberNode, ParseTreeNode* identifierNode);
	//Get linkedNonterminals for semantic check
	vector<ParseTreeNode*>& getLinkedMemberNonterminalsList();

protected:
	//methods
	
	virtual ParseTreeNode* getNodePtr() { return nullptr; };
	virtual void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode = nullptr) { return; };
	virtual void populateLocalSearchResultsList() { return; };
	
	
	
	//member variables
	
	Parser* parserPtr = nullptr;
	ParseTreeNode* parentNodePtr;
	vector<ParseTreeNode*> searchResultsList;
	//vector<ParseTreeNode*> symbolTable;
	string localClassType;
	vector<ParseTreeNode*> symbolTable; //symbolTable.first = TablePtr symbolTable.second == IdentifierPtr 
	ParseTreeNode* programNode_motherNode = nullptr;
	vector<ParseTreeNode*> linkedMemberNonterminals;
	
};