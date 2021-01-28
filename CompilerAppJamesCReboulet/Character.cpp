#include "Character.h"

Character::Character(string type, string character)
{
	this->tokenType = type;
	this->tokenValue = character;
}

string Character::getTokenType()
{
	return this->tokenType;
}
string Character::getTokenValue()
{
	return this->tokenValue;
}