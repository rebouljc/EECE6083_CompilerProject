#include "Character.h"

Character::Character(string type, string character)
{
	this->subTokenType = type;
	this->subTokenValue = character;
}

string Character::getTokenType()
{
	return this->subTokenType;
}
string Character::getTokenValue()
{
	return this->subTokenValue;
}