#include "Scanner.h"
#include <iostream>
#include <fstream>
#include <cmath>


Scanner::Scanner()
{
	this->populateReservedList();
	this->populatePunctuationList();
	this->populateAssignmentList();
	this->populateArithOperatorList();
	this->populateRelationOperatorList();
	this->populateBooleanOperatorList();
	this->populateWhitespaceSymbolsList();

	std::cout << "\nEnter a filename to be scanned.\n";
	string filename;
	std::cin >> filename;
	ifstream* input = new ifstream(filename);
	this->readFile(input);
}
void Scanner::populateReservedList()
{
	
	this->reserved.insert(make_pair("program", new Token("RESERVED_WORD", "program")));
	this->reserved.insert(make_pair("is", new Token("RESERVED_WORD", "is")));
	this->reserved.insert(make_pair("begin", new Token("RESERVED_WORD", "begin")));
	this->reserved.insert(make_pair("end", new Token("RESERVED_WORD", "end")));
	this->reserved.insert(make_pair("global", new Token("RESERVED_WORD", "global")));
	this->reserved.insert(make_pair("procedure", new Token("RESERVED_WORD", "procedure")));
	this->reserved.insert(make_pair("variable", new Token("RESERVED_WORD", "variable")));
	this->reserved.insert(make_pair("type", new Token("RESERVED_WORD", "type")));
	this->reserved.insert(make_pair("integer", new Token("RESERVED_WORD", "integer")));
	this->reserved.insert(make_pair("float", new Token("RESERVED_WORD", "float")));
	this->reserved.insert(make_pair("string", new Token("RESERVED_WORD", "string")));
	this->reserved.insert(make_pair("bool", new Token("RESERVED_WORD", "bool")));
	this->reserved.insert(make_pair("enum", new Token("RESERVED_WORD", "enum")));
	this->reserved.insert(make_pair("if", new Token("RESERVED_WORD", "if")));
	this->reserved.insert(make_pair("then", new Token("RESERVED_WORD", "then")));
	this->reserved.insert(make_pair("else", new Token("RESERVED_WORD", "else")));
	this->reserved.insert(make_pair("for", new Token("RESERVED_WORD", "for")));
	this->reserved.insert(make_pair("return", new Token("RESERVED_WORD", "return")));
	this->reserved.insert(make_pair("not", new Token("RESERVED_WORD", "not")));
	this->reserved.insert(make_pair("true", new Token("RESERVED_WORD", "true")));
	this->reserved.insert(make_pair("false", new Token("RESERVED_WORD", "false")));
}

void Scanner::populatePunctuationList()
{
	this->punctuation.insert(make_pair(".", new Token("PUNCTUATION", ".")));
	this->punctuation.insert(make_pair(";", new Token("PUNCTUATION", ";")));
	this->punctuation.insert(make_pair(",", new Token("PUNCTUATION", ",")));
	this->punctuation.insert(make_pair("(", new Token("PUNCTUATION", "(")));
	this->punctuation.insert(make_pair(")", new Token("PUNCTUATION", ")")));
	this->punctuation.insert(make_pair("{", new Token("PUNCTUATION", "{")));
	this->punctuation.insert(make_pair("}", new Token("PUNCTUATION", "}")));
	this->punctuation.insert(make_pair("[", new Token("PUNCTUATION", "[")));
	this->punctuation.insert(make_pair("]", new Token("PUNCTUATION", "]")));
	this->punctuation.insert(make_pair("-", new Token("PUNCTUATION", "-")));
	this->punctuation.insert(make_pair("\"", new Token("PUNCTUATION", "\"")));
	this->punctuation.insert(make_pair("^\"", new Token("PUNCTUATION", "^\"")));
	this->punctuation.insert(make_pair(":", new Token("PUNCTUATION", ":")));
	
}

void Scanner::populateAssignmentList()
{
    this->assignment.insert(make_pair(":=", new Token("ASSIGNMENT", ":=")));
	
	
}

void Scanner::populateArithOperatorList()
{
	this->arithOperator.insert(make_pair("+", new Token("ARITH_OPERATOR", "+")));
	this->arithOperator.insert(make_pair("-", new Token("ARITH_OPERATOR", "-")));
	this->arithOperator.insert(make_pair("*", new Token("ARITH_OPERATOR", "*")));
	this->arithOperator.insert(make_pair("/", new Token("ARITH_OPERATOR", "/")));
}

void Scanner::populateRelationOperatorList()
{
	this->relationOperator.insert(make_pair("<", new Token("RELATION_OP", "<")));
	this->relationOperator.insert(make_pair(">", new Token("RELATION_OP", ">")));
	this->relationOperator.insert(make_pair("<=", new Token("RELATION_OP", "<=")));
	this->relationOperator.insert(make_pair(">=", new Token("RELATION_OP", ">=")));
	this->relationOperator.insert(make_pair("==", new Token("RELATION_OP", "==")));
	this->relationOperator.insert(make_pair("!=", new Token("RELATION_OP", "!=")));
}

void Scanner::populateWhitespaceSymbolsList()
{
	this->whitespaceSymbols.push_back(' ');
	this->whitespaceSymbols.push_back('\t');
	this->whitespaceSymbols.push_back('\n');
}

void Scanner::createDigitCharacter(char character)
{
	string convertChar(1, character);

	this->storedCharacters.push_back(new Character("DIGIT", convertChar));
}
void Scanner::createLetterCharacter(char character)
{
	string convertChar(1, character);
	
    this->storedCharacters.push_back(new Character("LETTER", convertChar));
	
}

void Scanner::createSingleCharacterToken(Token* token)
{
	this->storedTokens.push_back(new Token(token->getTokenType(), token->getTokenValue()));
}
void Scanner::createAssignmentToken()
{

}
void Scanner::createArithOperatorToken()
{

}
void Scanner::createRelationOperatorToken()
{

}
void Scanner::createBooleanOperatorToken()
{

}
void Scanner::createReservedWordToken(Token* tokenToAdd)
{
	//Creates a token for an identified reserved word
	this->storedTokens.push_back(new Token(tokenToAdd));
}
void Scanner::createIdentifierToken()
{

	this->storedTokens.push_back(new Token());
	Token* recentToken = this->storedTokens.at(this->storedTokens.size()-1);
	string identifier;

	for (int i = 0; i < this->storedCharacters.size(); ++i)
	{
		identifier.push_back(this->storedCharacters.at(i)->getTokenValue()[0]);
		recentToken->setTokenValue(identifier);
	}
	//make sure to clear the stored characters list or a pile will form.
	this->storedCharacters.clear();
}

void Scanner::createStringLiteralToken()
{

}

void Scanner::createNumberToken(string type, double value)
{
	this->storedTokens.push_back(new Token("NUMBER", value));
}

char Scanner::readCharacterFromFile(ifstream* inputStream)
{
	char currentCharacter;

	inputStream->get(currentCharacter);
	return currentCharacter;
}

char Scanner::peekNextCharacterInFile(ifstream* inputStream)
{
	return inputStream->peek();
}



void Scanner::populateBooleanOperatorList()
{
	this->booleanOperator.insert(make_pair("&", new Token("BOOLEAN_OP", "&")));
	this->booleanOperator.insert(make_pair("|", new Token("BOOLEAN_OP", "|")));
}


Token* Scanner::searchPunctuationList(string character)
{
	
	for (set<pair<string, Token*>>::iterator it = this->punctuation.begin(); it != this->punctuation.end(); ++it)
	{
		if (character == it->first)
		{
			return it->second;
		}
	}
	return nullptr;
}
Token* Scanner::searchAssignmentList(string character, ifstream* input)
{
	char peekChar = this->peekNextCharacterInFile(input);
	string checkPeekString = character;
	checkPeekString.push_back(peekChar);

	for (set<pair<string, Token*>>::iterator it = this->assignment.begin(); it != this->assignment.end(); ++it)
	{
		if (checkPeekString == it->first)
		{
			//We need to read and disguard that character, so it doesn't screw things up in the input stream later.
			char byteWaste = this->readCharacterFromFile(input);
			return it->second;
		}
	}
	return nullptr;
}
Token* Scanner::searchArithOperatorList(string character)
{
	for (set<pair<string, Token*>>::iterator it = this->arithOperator.begin(); it != this->arithOperator.end(); ++it)
	{
		if (character == it->first)
		{
			return it->second;
		}
	}
	return nullptr;
}

//This will never return anything because only one character is being sent at a time.
//We have to look ahead and see if there is a match.  Involves passing pointers all over the place for the inputStream.

Token* Scanner::searchRelationOperatorList(string character,ifstream* input)
{
	char peekChar = this->peekNextCharacterInFile(input);
	string checkPeekString = character;
	checkPeekString.push_back(peekChar);
	for (set<pair<string, Token*>>::iterator it = this->relationOperator.begin(); it != this->relationOperator.end(); ++it)
	{
		if (checkPeekString == it->first)
		{
			//We need to read and disguard that character, so it doesn't screw things up in the input stream later.
			char byteWaste = this->readCharacterFromFile(input);
			return it->second;
		}
	}
	return nullptr;
}
Token* Scanner::searchBooleanOperatorList(string character) 
{
	for (set<pair<string, Token*>>::iterator it = this->booleanOperator.begin(); it != this->booleanOperator.end(); ++it)
	{
		if (character == it->first)
		{
			return it->second;
		}
	}
	return nullptr;
}

Token* Scanner::searchSingleCharacterLists(string character, ifstream* input)
{
	Token* result;

	if ((result = searchRelationOperatorList(character,input)) != nullptr)
		return result;
	else if ((result = searchAssignmentList(character, input)) != nullptr)
		return result;
	else if ((result = searchPunctuationList(character)) != nullptr)
		return result;
	else if ((result = searchArithOperatorList(character)) != nullptr)
		return result;
	
	else if ((result = searchBooleanOperatorList(character)) != nullptr)
		return result;
	
	return nullptr;
}

Token* Scanner::searchReservedWordList(string character)
{

for (set<pair<string, Token*>>::iterator it = this->reserved.begin(); it != this->reserved.end(); ++it)
{
	if (character == it->first)
	{
		return it->second;
	}
}

return nullptr;
}

void Scanner::matchReservedWord()
{
	//We first have to obtain the string, so we empty the vector of stored characters into a string and then check.
	string searchString;
	for (unsigned int i = 0; i < this->storedCharacters.size(); ++i)
	{
		searchString.push_back(this->storedCharacters.at(i)->getTokenValue()[0]);
	}

	//Now, search the reserved Words list.
	Token* resultTok;
	if ((resultTok = this->searchReservedWordList(searchString)) != nullptr)
	{
		//create the reserved word token
		this->createReservedWordToken(resultTok);

		//if we have identified a lexeme as a reserved word, make sure to empty the character vector.
		this->storedCharacters.clear();
		
	}

	else
	{
		this->otherActionMatchNotReservedWord();
		//this->matchNumber();  //**Need to put this in for later. For matching numbers.
	}
	
}

void Scanner::otherActionMatchNotReservedWord()
{
	if (this->storedCharacters.empty())
	{
		return;
	}
	
	else if (!matchIdentifier())
	{
		this->matchNumber();
	}
}

bool Scanner::matchIdentifier()
{
	 
     if (this->storedCharacters.at(0)->getTokenType() == "DIGIT")
	 {
		return false;
	 }

	 this->createIdentifierToken();

	 return true;
	


}

void Scanner::matchNumber()
{
	//verify that everything is a digit first.
	
	for (int i = 0; i < this->storedCharacters.size(); ++i)
	{
		if (this->storedCharacters.at(i)->getTokenType() == "LETTER")
		{
			return;
		}
	}
	
	//If we get here, they must all be digits or we would have gotten the hell out of here above.
    //Ah, what to do next??  Take an Ambien, write some more code, commit to the repository, and then wake up the next morning and curse at all of the crazy mistakes.
    //Here we go!~~~~~~

	//First, we convert all characters to integers.

	vector<int> intVector;

	for (int i = 0; i < this->storedCharacters.size(); ++i)
	{
		if (this->storedCharacters.at(i)->getTokenType() == "DIGIT")
		{
			intVector.push_back(stoi(this->storedCharacters.at(0)->getTokenValue(), nullptr, 10));
		}
	}

	double initialInput = 0;
	double initialExponent = 1;
	double finalResult = this->computeFloatingPointResult(&intVector, initialInput, initialExponent);

	//Now, create the double token.
	
	this->createNumberToken("NUMBER", finalResult);

	//Remember to clear the characters
	this->storedCharacters.clear();


}

double Scanner::computeFloatingPointResult(vector<int>* inputVector, double input, double exponent)
{

	double currentValue = std::pow(inputVector->at(inputVector->size() - 1), exponent);
	inputVector->pop_back(); //We have processed that element.  Now delete it, so we don't run into infinite recursion.

	if (inputVector->empty())
	{
		return currentValue;
	}

	return currentValue + this->computeFloatingPointResult(inputVector, input, ++exponent);
	
}

void Scanner::matchLetter()
{

}

void Scanner::matchStringLiteral()
{

}
//This is the primary Scanner method that will be utilized in this application - compilation of all of the other methods.

void Scanner::readFile(ifstream* input)
{


	//Read the character from the file.

	char character = readCharacterFromFile(input);
	if (input->eof())
	{
		return;
	}
	else if (isalpha(character))
	{
		this->createLetterCharacter(character);
		
		

	}

	else if (isdigit(character))
	{
		this->createDigitCharacter(character);
		
		
	}

	else //Not a letter or a digit, so perform an alternative action.  
	{
		performOtherAction(input, character);
	}
	this->readFile(input); //The recursive call is made until EOF is encountered.
	
	return;
	
}



void Scanner::reportError()
{

}

void Scanner::reportWarning()
{

}

void Scanner::performOtherAction(ifstream* input, char character)
{
	
	string charToString(1, character); //Convert char character to string, so that it can be used by class methods.
	Token* singleCharTok;

	//check for whitespace
	if (this->isWhitespace(character))
	{
		//We either need to create the token as a letter, number, reserved word, or identifier.  How do we decide?
		//We need to call Scanner::matchReservedWord() which will start checking the reservedWords list for a match;
		this->matchReservedWord();
	}
	

	else if ((singleCharTok = this->searchSingleCharacterLists(charToString, input)) != nullptr)
	{
		//Match the reserved word
		this->matchReservedWord();

		//create a token for the single character mark
		this->createSingleCharacterToken(singleCharTok);
		
	}


	//NOTE:  Right now the program is blowing up, because we are not calling this->storedCharacters.clear() yet except when we encounter a reserved word.  
	//Maybe I will briefly do this to see whether the scanner can recognize digits.

	return;
}

bool Scanner::isWhitespace(char character)
{
	for (unsigned int i = 0; i < this->whitespaceSymbols.size(); ++i)
	{
		if (this->whitespaceSymbols.at(i) == character)
		{
			return true;
		}
	}

	return false;
}

