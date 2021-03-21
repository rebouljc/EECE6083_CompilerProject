#include "Scanner.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include "StringLiteralException.h"
#include "IdentifierBeginsWithNumberException.h"
#include "NoClosingCommentMarkException.h"
#include "IllegalEqualsSignException.h"
#include "IllegalIdentifierException.h"
#include "NoPeriodAtEndOfProgramException.h"
#include "MainCompileErrorException.h"


//This scanner is guaranteed not to crap out.  If something is wrong, it will immediately stop at the line of the first instance of
//the problem and throw an exception.  I will not continue to further processing and throw out 100 unrelated compiler errors in the process,
//when the REAL problem was that the user simply used an illegal character or forgot to properly close their comments with */, etc.
//The trick is to catch as many errors as possible the earliest in the process, to prevent it from continuing and trying to recover from
//terrible scenarios and generating hundreds of issues in the process.  If the user writes code wrong, IT IS JUNK and needs to be FIXED NOW!
//None of this Donald Trump impeachment crap - "I didn't mean that..."  No, you SAID IT and DIDN'T IMMEDIATELY CORRECT IT IF YOU HAD SPOKEN WRONG so that is WHAT YOU MEANT!

Scanner::Scanner()
{
	
}

void Scanner::cleanUp()
{
	for (set<pair<string, Token*>>::iterator it= this->reserved.begin(); it != this->reserved.end(); ++it)
	{
		delete(it->second);
	}

	for (set<pair<string, Token*>>::iterator it = this->punctuation.begin(); it != this->punctuation.end(); ++it)
	{
		delete(it->second);
	}

	for (set<pair<string, Token*>>::iterator it = this->assignment.begin(); it != this->assignment.end(); ++it)
	{
		delete(it->second);
	}

	for (set<pair<string, Token*>>::iterator it = this->arithOperator.begin(); it != this->arithOperator.end(); ++it)
	{
		delete(it->second);
	}

	for (set<pair<string, Token*>>::iterator it = this->relationOperator.begin(); it != this->relationOperator.end(); ++it)
	{
		delete(it->second);
	}

	for (set<pair<string, Token*>>::iterator it = this->booleanOperator.begin(); it != this->booleanOperator.end(); ++it)
	{
		delete(it->second);
	}

	for (unsigned int i = 0; i < this->storedCharacters.size(); ++i)
	{
		delete(this->storedCharacters.at(i));
	}

}


void Scanner::init()
{
	this->lineNumber = 1;
	this->populateReservedList();
	this->populatePunctuationList();
	this->populateAssignmentList();
	this->populateArithOperatorList();
	this->populateRelationOperatorList();
	this->populateBooleanOperatorList();
	this->populateWhitespaceSymbolsList();

	this->lineNumber = 1;

	std::cout << "\nEnter a filename to be scanned.\n";
	string filename;
	std::cin >> filename;
    ifstream* input = new ifstream(filename);
	this->readFile(input);
	input->close();
	delete input;
	try
	{
		if (!this->storedTokens.empty())
		{
			Token* checkPeriod = this->storedTokens.at(this->storedTokens.size() - 1);
			if (checkPeriod->getTokenValue() != ".")
			{
				throw NoPeriodAtEndOfProgramException();
			}
		}
	}
	catch (NoPeriodAtEndOfProgramException& e)
	{
		cout << endl << e.what() << this->getLineNumber();
		//Now, we have to add that token.
		this->storedTokens.push_back(new Token("PUNCTUATION", "."));
	}
}

void Scanner::incrementLineNumber()
{
	this->lineNumber++;
}

int Scanner::getLineNumber()
{
	return this->lineNumber;
}

int Scanner::getFirstCommentLineNumber()
{
	return this->firstCommentLineNumber;
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

	this->relationOperator.insert(make_pair("= ", new Token("ILLEGAL_ASSIGNMENT_OP", "= ")));
	this->relationOperator.insert(make_pair("~", new Token("ILLEGAL_ASSIGNMENT_OP", "~ ")));
	this->relationOperator.insert(make_pair("! ", new Token("ILLEGAL_ASSIGNMENT_OP", "! ")));
	this->relationOperator.insert(make_pair("? ", new Token("ILLEGAL_ASSIGNMENT_OP", "? ")));
	this->relationOperator.insert(make_pair("@ ", new Token("ILLEGAL_ASSIGNMENT_OP", "@ ")));
	this->relationOperator.insert(make_pair("' ", new Token("ILLEGAL_ASSIGNMENT_OP", "' ")));
	this->relationOperator.insert(make_pair("`", new Token("ILLEGAL_ASSIGNMENT_OP", "` ")));
	this->relationOperator.insert(make_pair("$ ", new Token("ILLEGAL_ASSIGNMENT_OP", "$ ")));
	this->relationOperator.insert(make_pair("% ", new Token("ILLEGAL_ASSIGNMENT_OP", "% ")));
	this->relationOperator.insert(make_pair("# ", new Token("ILLEGAL_ASSIGNMENT_OP", "# ")));

	this->relationOperator.insert(make_pair("=\n", new Token("ILLEGAL_ASSIGNMENT_OP", "=\n")));
	this->relationOperator.insert(make_pair("~\n", new Token("ILLEGAL_ASSIGNMENT_OP", "~\n")));
	this->relationOperator.insert(make_pair("!\n", new Token("ILLEGAL_ASSIGNMENT_OP", "!\n")));
	this->relationOperator.insert(make_pair("?\n", new Token("ILLEGAL_ASSIGNMENT_OP", "?\n")));
	this->relationOperator.insert(make_pair("@\n", new Token("ILLEGAL_ASSIGNMENT_OP", "@\n")));
	this->relationOperator.insert(make_pair("'\n", new Token("ILLEGAL_ASSIGNMENT_OP", "'\n")));
	this->relationOperator.insert(make_pair("`\n", new Token("ILLEGAL_ASSIGNMENT_OP", "`\n")));
	this->relationOperator.insert(make_pair("$\n", new Token("ILLEGAL_ASSIGNMENT_OP", "$\n")));
	this->relationOperator.insert(make_pair("%\n", new Token("ILLEGAL_ASSIGNMENT_OP", "%\n")));
	this->relationOperator.insert(make_pair("#\n", new Token("ILLEGAL_ASSIGNMENT_OP", "#\n")));

	

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

void Scanner::createPeriodCharacter()
{
	this->storedCharacters.push_back(new Character("PERIOD", "."));
}

void Scanner::createSingleCharacterToken(Token* token)
{
	this->storedTokens.push_back(new Token(token->getTokenType(), token->getTokenValue(), this->lineNumber));
}

void Scanner::createReservedWordToken(Token* tokenToAdd)
{
	
	this->storedTokens.push_back(new Token(tokenToAdd, this->lineNumber));
	
}
void Scanner::createIdentifierToken()
{

	this->storedTokens.push_back(new Token(this->lineNumber));
	Token* recentToken = this->storedTokens.at(this->storedTokens.size()-1);
	string identifier;

	for (unsigned int i = 0; i < this->storedCharacters.size(); ++i)
	{
		identifier.push_back(tolower(this->storedCharacters.at(i)->getTokenValue()[0]));
		recentToken->setTokenValue(identifier);
	}
	//make sure to clear the stored characters list or a pile will form.
	for (unsigned int i = 0; i < this->storedCharacters.size(); ++i)
	{
		delete (this->storedCharacters.at(i));
	}
	this->storedCharacters.clear();
}

void Scanner::createStringLiteralToken()
{
	//Else, we get down to business and then return.
	this->storedTokens.at(this->storedTokens.size() - 1)->setTokenType("STRING_LITERAL");

	//Now, create the string.  We can ignore the puntuation now, and save later processing
	string newString;

	//Read the character from the file.

	for (unsigned int i = 0; i < this->storedCharacters.size(); ++i)
	{
		newString = newString + this->storedCharacters.at(i)->getTokenValue();
	}

	//Oh yeah!  We need to actually set the token value too..  I forgot.
	this->storedTokens.at(this->storedTokens.size() - 1)->setTokenValue(newString);
	//Now, as always, we need to clear the character list
	for (unsigned int i = 0; i < this->storedCharacters.size(); ++i)
	{
		delete (this->storedCharacters.at(i));
	}
	this->storedCharacters.clear();
}

void Scanner::createNumberToken(string type, double value)
{
	this->storedTokens.push_back(new Token("NUMBER", value, this->lineNumber));
}

char Scanner::readCharacterFromFile(ifstream* inputStream)
{
	char currentCharacter;
	inputStream->get(currentCharacter);

	if (currentCharacter == '\n')
	{
		this->incrementLineNumber();
	}
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
			//We need to read and discard that character, so it doesn't screw things up in the input stream later.
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
	set<pair<string, Token*>>::iterator it;
	try
	{
		for ( it = this->relationOperator.begin(); it != this->relationOperator.end(); ++it)
		{
			if (checkPeekString == it->first)
			{
				if (it->second->getTokenType() == "ILLEGAL_ASSIGNMENT_OP")
				{
					throw IllegalEqualsSignException();
				}
				//We need to read and discard that character, so it doesn't screw things up in the input stream later.
				char byteWaste = this->readCharacterFromFile(input);
				//Now, we need to read letters into the stored character array until we encounter a space character
				return it->second;
			}


		}
	}
	catch (IllegalEqualsSignException& e)
	{
		cout << endl << e.what() << this->getLineNumber();
		
		for (set<pair<string, Token*>>::iterator punctIt = this->punctuation.begin(); punctIt != this->punctuation.end(); ++punctIt)
		{
			if (punctIt->first == ":")
			{   
				char byteWaste = this->readCharacterFromFile(input);
				punctIt->second->setTokenType("ASSIGNMENT");
				punctIt->second->setTokenValue(":=");
				return punctIt->second;
			}
		}
		

		//it = i - 1; //Get the address of the character before the illegal equals sign.
		//this->storedCharacters.insert(i, new Character())
	}
	for (it = this->relationOperator.begin(); it != this->relationOperator.end(); ++it)
	{
		string checkRelationChar = character;
		if (checkRelationChar == it->first && it->second->getTokenType() == "RELATION_OP")
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

void Scanner::matchReservedWord(ifstream* input)
{
	//We first have to obtain the string, so we empty the vector of stored characters into a string and then check.
	string searchString;
	for (unsigned int i = 0; i < this->storedCharacters.size(); ++i)
	{
		searchString.push_back(tolower(this->storedCharacters.at(i)->getTokenValue()[0]));
	}

	//Now, search the reserved Words list.
	Token* resultTok;
	if ((resultTok = this->searchReservedWordList(searchString)) != nullptr)
	{
		//create the reserved word token
		this->createReservedWordToken(resultTok);

		//if we have identified a lexeme as a reserved word, make sure to empty the character vector.
		for (unsigned int i = 0; i < this->storedCharacters.size(); ++i)
		{
			delete (this->storedCharacters.at(i));
		}
		this->storedCharacters.clear();
		
	}

	else
	{
		this->otherActionMatchNotReservedWord(input);
	}
	
}

void Scanner::otherActionMatchNotReservedWord(ifstream* input)
{

	
	if (this->storedCharacters.empty())
	{
		return;
	}

	
	else if (!matchIdentifier())
	{
		this->matchNumber(input);
	}
}

bool Scanner::matchIdentifier()
{
	//search the whole damn list, since this doesn't work if the character is in the middle of the list.
	//It is slightly inefficient, but what do you do??
	vector<Character*>::iterator i;
	try
	{
		for (i = this->storedCharacters.begin(); i != this->storedCharacters.end(); ++i)
		{
		
			if ((*i)->getTokenType()  == "BAD_BOY")
			{
				throw IllegalIdentifierException();
				return false;
			}
		}
	}

	catch (IllegalIdentifierException &e)
	{
		cout << endl << e.what() << this->getLineNumber();
		this->storedCharacters.erase(i);
	}

     if (this->storedCharacters.at(0)->getTokenType() == "DIGIT")
	 {
		return false;
	 }
	
	 this->createIdentifierToken();

	 return true;	
}

void Scanner::matchNumber(ifstream* input)
{
	//verify that everything is a digit first.
	vector<Character*>::iterator i;
	try
	{
		for (i = this->storedCharacters.begin(); i != this->storedCharacters.end(); ++i)
		{
			if ((*i)->getTokenType() == "LETTER")
			{
				//Here is where we throw the exception.  We obviously have an identifier that starts with a digit and contains a letter.  BAD!

				throw IdentifierBeginsWithNumberException();
				return;
			}

			else if ((*i)->getTokenType() == "BAD_BOY")
			{
				throw IllegalEqualsSignException();
			}
		}
	}

	catch (IdentifierBeginsWithNumberException &e)
	{
		cout << endl << e.what() << this->getLineNumber();

		//Remove the DIGIT from the identifier and insert it at the end of the variable name.
		//Then continue.  But throw the error.  
		//If there are any errors present, the compiler will halt before Intermediate Code generation.

		Character* oldChar = new Character((*i)->getTokenType(), (*i)->getTokenValue());
		this->storedCharacters.erase(i);
		this->storedCharacters.push_back(new Character(oldChar->getTokenType(), oldChar->getTokenValue()));
	}

	
	
	//First, we convert all characters to integers.
	
	vector<int> intVector;
	string intString;
	double finalResult = 0;

	for (unsigned int i = 0; i < this->storedCharacters.size(); ++i)
	{
		if (this->storedCharacters.at(i)->getTokenType() == "DIGIT")
		{
			intVector.push_back(stoi(this->storedCharacters.at(i)->getTokenValue(), NULL, 10));
			intString.push_back(this->storedCharacters.at(i)->getTokenValue()[0]);
		}
	}

	//First, we check to see whether the last token was a period symbol.  I try to keep things clean and then all of the issues start happening and the 
	//code starts to get dirtier.
	Token* lastStoredTokenPtr = this->storedTokens.at(this->storedTokens.size() - 1);
	if (lastStoredTokenPtr->getIsPeriodStatus())
	{
		this->storedTokens.pop_back(); //Get rid of that period token RIGHT NOW!  YES! I finally got the floating point token created!!!
		finalResult = this->computeFloatingPointLiteralResult(&intVector);
		this->storedTokens.at(this->storedTokens.size() - 1)->setTokenType("NUMBER");
		this->storedTokens.at(this->storedTokens.size() - 1)->setTokenValue("FLOATING_POINT_LITERAL");
		this->storedTokens.at(this->storedTokens.size() - 1)->setDoubleNumberTokenValue(finalResult + (this->storedTokens.at(this->storedTokens.size() - 1)->getIntegerDoubleNumberTokenValue()));
		
	}
	
	else
	{
		//Now, create the integer_literal token.

		
		finalResult = this->computeIntegerLiteralResult(&intVector, 0, intVector.size());
		this->createNumberToken("NUMBER", finalResult);
	}

	//Remember to clear the characters
	for (unsigned int i = 0; i < this->storedCharacters.size(); ++i)
	{
		delete (this->storedCharacters.at(i));
	}
	this->storedCharacters.clear();
	
	return;
}

double Scanner::computeFloatingPointLiteralResult(vector<int>* intVector)
{ 
	string intString = "0";
	intString += ".";

	for (unsigned int i = 0; i < this->storedCharacters.size(); ++i)
	{
		if (this->storedCharacters.at(i)->getTokenType() == "DIGIT")
		{
			
			intString += this->storedCharacters.at(i)->getTokenValue()[0];
		}
	}
	string::size_type sizeString;
	return stod(intString, &sizeString);    
}

double Scanner::computeIntegerLiteralResult(vector<int>* inputVector, int vecStartElement, double vectorSize)
{
	--vectorSize; //be sure to decrement exponent by 1 for vector size or it will decemate the calculation, when the method recurses.  

	double currentValue = inputVector->at(vecStartElement);
	++vecStartElement;

	if (vecStartElement == inputVector->size())
	{
		
		return currentValue;
	}

	currentValue *= pow(10.0, vectorSize);
	
	return currentValue + (this->computeIntegerLiteralResult(inputVector, vecStartElement, vectorSize));
}

int Scanner::getFirstQuotationMarkLineNumber()
{
	return this->firstQuotationMarkLineNumber;
}

void Scanner::matchStringLiteral(ifstream* input)
{
	char character = readCharacterFromFile(input);
	try
	{
		if (input->eof()) //Prevents infinite recursion if user forgets to end string literal with "
		{
			throw StringLiteralException();
			//Here is where we throw the exception.  We forgot the quotation marks and we have no idea where the string token ends.
			//For now, we will just return.  Now, if we ever get here, we can be assured that the developer forgot a closing and/or opening " and
			//if we don't produce an error, we will have parsed and created a bunch of bullshit tokens, which is what happened when I tested it.

			return;
		}
	}
	catch (StringLiteralException& e)
	{
		cout << endl << e.what() << this->getFirstQuotationMarkLineNumber();
		throw MainCompileErrorException();
		
	}

	if (isalpha(character) || character == '_')
	{
		this->createLetterCharacter(character);
	}
	
	else if (isdigit(character))
	{
		this->createDigitCharacter(character);
	}

	
	else if (character == '"')
	{
		
		this->createStringLiteralToken();
		
		
		return;
	}
	
	this->matchStringLiteral(input); //recurse back.
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

	else if (isalpha(character) || character == '_')
	{
		this->createLetterCharacter(character);
	}

	
	else if (character == '~' || character == '!' ||
		     character == '?' || character == '@' ||
		     character == '\''|| character == '`' ||
		     character == '$' || character == '%' ||
		     character == '#'
		    )
	{
		string charToPush(1, character);
		this->storedCharacters.push_back(new Character("BAD_BOY", charToPush));
	}

	else if (isdigit(character))
	{
		this->createDigitCharacter(character);
	}

	else //Not a letter or a digit, so perform an alternative action.  
	{
		performOtherAction(input, character);

		//We have to put a corrective hack in to prevent the line number on a token from being incorrectly incremented when it has
		//an '\n' after it.  For instance, after the reserved word "is" or the identifier "is".  This only took about 4 hours to figure out.

		if (!(this->storedTokens.empty()) && character == '\n')
		{
			this->storedTokens.at(this->storedTokens.size() - 1)->setTokenLineNumber(this->lineNumber - 1);
		}
	}
	this->readFile(input); //The recursive call is made until EOF is encountered.
	
	return;
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
		this->matchReservedWord(input);
	}
	
	else if ((singleCharTok = this->searchSingleCharacterLists(charToString, input)) != nullptr)
	{
		//Match the reserved word
		this->matchReservedWord(input);

		//create a token for the single character mark
		this->createSingleCharacterToken(singleCharTok);

		//If the token is a '.' symbol, we need to set the period status flag to true;
		if (this->storedTokens.at(this->storedTokens.size() - 1)->getTokenValue() == ".")
		{
			this->storedTokens.at(this->storedTokens.size() - 1)->setTokenIsPeriodStatus(true);

			//If this is so, call this->matchReservedWordAgain()
			//Recurse back into the readFile again.  DOUBLE RECURSION, BABY!!  This is how you speak when you aren't getting any because
			//you are a CS major and have no time and no money. 

			this->readFile(input); //Then, it will go back to matchReservedWord(input).
		}

		//But, if we see a " symbol, we know that we must have a string literal, so we go directly to that method and parse it out.
		//If we don't do it here, then this method will recurse and check for a reserved word and create an identifier instead of string literal.

		else if (this->storedTokens.at(this->storedTokens.size() - 1)->getTokenValue() == "\"")
		{
			this->firstQuotationMarkLineNumber = this->lineNumber;
			this->matchStringLiteral(input);
		}
		//Else, we consider it a comment and we start ignoring comments

		else if (this->storedTokens.at(this->storedTokens.size() - 1)->getTokenValue() == "/" ||
			     this->storedTokens.at(this->storedTokens.size() - 1)->getTokenValue() == "*") // We do the comment checking and ignoring.
		{
	        //We have to peek ahead, though and return immediately if we do not see another "/".  Then we have an ARITH_OPERATOR token.
			
			char peekChar = this->peekNextCharacterInFile(input);
			if (peekChar == '/' || peekChar == '*')
			{
				//Get rid of the ARITH_OPERATOR token that was just added by the previous state
				this->storedTokens.pop_back();
				this->commentCheckingIgnoringDecisionMethod(input);	
			}	
		}
	}
 
	if (!this->storedTokens.empty())
	{
		
		if ( (this->storedTokens.at(0)->getTokenValue()) != "program" )
		{
			throw NoClosingCommentMarkException();
		}
		
	}
	
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

void Scanner::commentCheckingIgnoringDecisionMethod(ifstream* input)
{
	char readNextCharacter = this->readCharacterFromFile(input);

	if (readNextCharacter == '\n')
	{
		return;
	}

	else if (readNextCharacter == '*')
	{
		this->firstCommentLineNumber = this->lineNumber;
		this->embeddedCommentsCheckingAndIgnoringAncillaryMethod(input);
		
	}

	else if (readNextCharacter == '/')
	{	
			this->commentCheckingAndIgnoringAncillaryMethod(input);
	}

	return;
}

void Scanner::commentCheckingAndIgnoringAncillaryMethod(ifstream* input)
{
	char readNextCharacter = this->readCharacterFromFile(input);

	if (readNextCharacter == '\n')
	{	
		return;
	}
	//Waste and recurse until '\n' is encountered, then return.
	char wasteChar = this->readCharacterFromFile(input);
	this->commentCheckingAndIgnoringAncillaryMethod(input);
}

void Scanner::embeddedCommentsCheckingAndIgnoringAncillaryMethod(ifstream* input)
{
	char readNextCharacter = this->readCharacterFromFile(input);
	
	if(input->eof())
	{
		
		throw NoClosingCommentMarkException();
		
	}
	
	else if (readNextCharacter == '*')
	{
		//We have to do another peek to see if we have a closing */  Otherwise, we will probably parse bullshit again.
		char peekChar = this->peekNextCharacterInFile(input);
		if (peekChar == '/')
		{	
			char wasteToken = this->readCharacterFromFile(input);
			return;
		}
	}
	//Takes care of case where there is a '/' within the embedded comment.
	else if (readNextCharacter == '/')
	{
		this->commentCheckingAndIgnoringAncillaryMethod(input);
	}

	//Waste and recurse until '*' is encountered, then return.  I forgot to waste.
	char wasteChar = this->readCharacterFromFile(input);
	this->embeddedCommentsCheckingAndIgnoringAncillaryMethod(input);
}


