#include "Token.h"

Token::Token()
{
	this->tokenType = "IDENTIFIER";
	
}

Token::Token(int tokLineNumber)
{
	this->tokenType = "IDENTIFIER";
	this->tokenLineNumber = tokLineNumber;
}

Token::Token(string tokenType, string tokenValue, int tokenLineNumber)
{
	this->tokenType = tokenType;
	this->tokenValue = tokenValue;
	this->tokenLineNumber = tokenLineNumber;
}
Token::Token(string tokenType, string tokenValue)
{
	this->tokenType = tokenType;
	this->tokenValue = tokenValue;

}

Token::Token(Token* token, int tokLineNumber)
{
	this->tokenType = token->getTokenType();
	this->tokenValue = token->getTokenValue();
	this->tokenLineNumber = tokLineNumber;
}

Token::Token(string tokenType, double numberValue)
{
	this->tokenType = tokenType;
	this->tokenValue = "INTEGER_LITERAL";
	this->integerNumberTokenValue = numberValue;
}

Token::Token(string tokenType, double numberValue, int tokenLineNumber)
{
	this->tokenType = tokenType;
	this->tokenValue = "INTEGER_LITERAL";
	this->integerNumberTokenValue = numberValue;
	this->tokenLineNumber = tokenLineNumber;
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


void Token::setTokenIsPeriodStatus(bool setting)
{
	this->isPeriod = setting;
}
bool Token::getIsPeriodStatus()
{
	return this->isPeriod;
}

void Token::setDoubleNumberTokenValue(double value)
{
	this->integerNumberTokenValue = value;
}

double Token::getIntegerDoubleNumberTokenValue()
{
	return this->integerNumberTokenValue;
}

int Token::getTokenLineNumber()
{
	return this->tokenLineNumber;
}

void Token::setTokenLineNumber(int tokLineNumber)
{
	this->tokenLineNumber = tokLineNumber;
}


