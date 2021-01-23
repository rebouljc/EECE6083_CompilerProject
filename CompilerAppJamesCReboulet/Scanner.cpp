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

	this->readFile();
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

bool Scanner::matchReservedWord()
{
	return false;
}

//This is the primary Scanner method that will be utilized in this application - compilation of all of the other methods.

void Scanner::readFile()
{
	std::cout << "\nEnter a filename to be scanned.";
	string filename;
	std::cin >> filename;
	ifstream* input = new ifstream(filename);

	//Read the character from the file.

	string character = readCharacterFromFile(input);

	//Check if there is a match to an existing token (punctuation, assignment, arithOp, relationalOp, or booleanOp.
	//*********TODO******* I forgot, we also need to add a method to determine whether the character is an integer, a floating point, or a letter.
	Token* result;
	//If this is true, create a token for that character.
	//Else, continue reading characters until a space is encountered and read them into a string.  Then, check to see if anyone of them matches a reserved word.  
	//If so, create a token for the reserved word.
	//Else, we consider that string to be an identifier and we create a token for each identifier.
	//
	if ((result = searchSingleCharacterLists(character)) != nullptr)
	{
		
	}
	//Determine if the next character is a space.  If so, check to see if the character is a letter or a number.
	else
	{

	}
	
}

string Scanner::readCharacterFromFile(ifstream* inputStream)
{
	char currentCharacter;

	inputStream->get(currentCharacter);
	string stringEquivChar(1, currentCharacter);

	return stringEquivChar;
}

void Scanner::reportError()
{

}

void Scanner::reportWarning()
{

}

