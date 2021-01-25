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

Token::Token(Token* token)
{
	this->tokenType = token->getTokenType();
	this->tokenValue = token->getTokenValue();
}

bool Token::operator ==(Token* tok)
{
	return false;
}

string Token::getTokenType()
{
	return tokenType;
}
string Token::getTokenValue()
{
	return tokenValue;
}

void Token::setTokenType(string type)
{
	tokenType = type;
}
void Token::setTokenValue(string value)
{
	tokenValue = value;
}

void Token::setTokenOccurrence(int occurrence)
{
	this->tokenOccurrence = occurrence;
}

void Token::setTokenLineNumber(string lineNumber)
{
	this->tokenLineNumber = lineNumber;
}
