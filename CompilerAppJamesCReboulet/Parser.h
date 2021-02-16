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
		~Parser();
		vector<Token*>* getStoredTokensList();
		Token* readNextToken();


	private:
		void parseTokensLoop();
		int indexToRead = 0;



	};
