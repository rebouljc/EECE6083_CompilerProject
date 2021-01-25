#include "Token.h"

Token::Token()
{
	this->tokenType = "IDENTIFIER";
}
Token::Token(string tokenType, string tokenValue)
{
	this->tokenType = tokenType;
	this->tokenValue = tokenValue;

}

bool Token::operator ==(Token* tok)
{
	return false;
}
void Token::setTokenOccurrence(int occurrence)
{
	this->tokenOccurrence = occurrence;
}

void Token::setTokenLineNumber(string lineNumber)
{
	this->tokenLineNumber = lineNumber;
}
