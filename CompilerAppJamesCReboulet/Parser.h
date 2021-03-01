#pragma once
#include "Scanner.h"
#include <iostream>
#include "Token.h"
#include "StringLiteralException.h"
#include "IdentifierBeginsWithNumberException.h"
#include "NoClosingCommentMarkException.h"
#include "IllegalEqualsSignException.h"
#include "IllegalIdentifierException.h"


   

	class Parser : public Scanner
	{
	public:
		Parser();
		void init();
		~Parser();
		vector<Token*>* getStoredTokensList();
		Token* readNextToken();
		Token* getCurrentlyReadToken();
		void resetTokenReadIndexToPrevious();


	private:
		void parseTokensLoop();
		int indexToRead = 0;
		Token* currentReadToken;
		


	};
