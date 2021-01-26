#include "Scanner.h"
#include <iostream>
#include <fstream>


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
	this->whitespaceSymbols.push_back('\t');
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

void Scanner::createPunctuationToken()
{

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

}

void Scanner::createStringLiteralToken()
{

}

char Scanner::readCharacterFromFile(ifstream* inputStream)
{
	char currentCharacter;

	inputStream->get(currentCharacter);
	return currentCharacter;
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
Token* Scanner::searchAssignmentList(string character)
{
	for (set<pair<string, Token*>>::iterator it = this->assignment.begin(); it != this->assignment.end(); ++it)
	{
		if (character == it->first)
		{
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
Token* Scanner::searchRelationOperatorList(string character)
{
	for (set<pair<string, Token*>>::iterator it = this->relationOperator.begin(); it != this->relationOperator.end(); ++it)
	{
		if (character == it->first)
		{
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

Token* Scanner::searchSingleCharacterLists(string character)
{
	Token* result;

	if ((result = searchPunctuationList(character)) != nullptr)
		return result;
	else if ((result = searchAssignmentList(character)) != nullptr)
		return result;
	else if ((result = searchArithOperatorList(character)) != nullptr)
		return result;
	else if ((result = searchRelationOperatorList(character)) != nullptr)
		return result;
	else if ((result = searchBooleanOperatorList(character)) != nullptr)
		return result;
	
	return nullptr;
}

Token* Scanner::searchReservedWordList(string character)
{
Token* result;
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
	}


}

//This is the primary Scanner method that will be utilized in this application - compilation of all of the other methods.

bool Scanner::matchPunctuation(string character)
{
	return false;
}

void Scanner::readFile(ifstream* input)
{


	//Read the character from the file.

	char character = readCharacterFromFile(input);
	if (character == EOF)
	{
		return;
	}
	else if (isalpha(character))
	{
		this->createLetterCharacter(character);
		this->readFile(input);

	}

	else if (isdigit(character))
	{
		this->createDigitCharacter(character);
		this->readFile(input);
	}

	else //Not a letter or a digit, so perform an alternative action.  
	{
		performOtherAction(input, character);
	}

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
	//check for whitespace
	char nextCharacter;
	string charToString;
	Token* singleCharTok;

	if (this->isWhitespace(character))
	{
		//We either need to create the token as a letter, number, reserved word, or identifier.  How do we decide?
		//We need to call Scanner::matchReservedWord() which will start checking the reservedWords list for a match;
		this->matchReservedWord();

		//nextCharacter = this->readCharacterFromFile(input);
	}
	

	else if ((singleCharTok = this->searchSingleCharacterLists(charToString)) != nullptr)
	{
		//Match the reserved word
		this->matchReservedWord();

		//create a token for the punctuation mark
	}
	else
	{
		//Throw a compiler error exception and terminate.
	}
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

