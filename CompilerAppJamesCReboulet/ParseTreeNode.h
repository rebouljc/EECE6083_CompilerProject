#pragma once
#include <vector>
#include "Token.h"
#include "Parser.h"



class ParseTreeNode
{
public:
	
	vector<ParseTreeNode*>* getSearchResultsList(ParseTreeNode* currentProgramNodePtr);
	
	void addToSearchResultsList(ParseTreeNode* nodeToAdd);
	void addToSymbolTable(ParseTreeNode* nodeToAdd);
	virtual void populateSearchResultsList(ParseTreeNode* motherNode = nullptr) { return; };
	vector<ParseTreeNode*>* getSymbolTable();
	virtual void setIsValid(bool isValid) {};
	virtual bool getIsValid() { return false; };
	void setParserPtr(Parser* parserPtr);
	virtual ~ParseTreeNode() {};
	
	
protected:
	//methods
	
	virtual ParseTreeNode* getNodePtr() { return nullptr; };
	virtual void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode = nullptr) { return; };
	
	

	//member variables
	
	Parser* parserPtr;
	vector<ParseTreeNode*> searchResultsList;
	vector<ParseTreeNode*> symbolTable;
	
};