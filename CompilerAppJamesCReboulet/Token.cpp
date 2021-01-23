#include "Token.h"


Token::Token(string tokenType, string tokenValue)
{
	this->tokenType = tokenType;
	this->tokenValue = tokenValue;

}

bool Token::operator ==(Token* tok)
{
	return false;
}
