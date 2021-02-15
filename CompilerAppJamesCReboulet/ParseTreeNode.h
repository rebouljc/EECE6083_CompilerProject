#pragma once
#include <vector>
#include "Token.h"
#include "Parser.h"



class ParseTreeNode
{
public:
	virtual ParseTreeNode* getNodePtr() { return nullptr; };
	vector<ParseTreeNode*>* getSearchResultsList(ParseTreeNode* currentProgramNodePtr);
	void setParserPtr(Parser* parserPtr);
	virtual void populateSearchResultsList(ParseTreeNode* motherNode = nullptr) { return; };
	void addToSearchResultsList(ParseTreeNode* nodeToAdd);
	void addToSymbolTable(ParseTreeNode* nodeToAdd);
	vector<ParseTreeNode*>* getSymbolTable();
protected:
	//methods
	
	virtual void verifySyntaxCreateParseTree(int tokenCounter, ParseTreeNode* motherNode = nullptr) { return; };
	
	Token* readNextToken();

	//member variables
	int indexToRead = 0;
	Parser* parserPtr;
	vector<ParseTreeNode*> searchResultsList;
	vector<ParseTreeNode*> symbolTable;
	
};