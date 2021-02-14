#pragma once
#include <vector>
#include "Parser.h"
#include "Token.h"

class ParseTreeNode
{
public:
	virtual ParseTreeNode* getNodePtr() { return nullptr; };
	vector<ParseTreeNode*>* getSearchResultsList(ParseTreeNode* currentProgramNodePtr);
	virtual void populateSearchResultsList(ParseTreeNode* motherNode = nullptr) { return; };
	void addToSearchResultsList(ParseTreeNode* nodeToAdd);
protected:
	//methods
	void setParserPtr(Parser* parserPtr);
	virtual void verifySyntaxCreateParseTree() { return; };
	
	Token* readNextToken();

	//member variables
	int indexToRead = 0;
	Parser* parserPtr;
	vector<ParseTreeNode*> searchResultsList;
};