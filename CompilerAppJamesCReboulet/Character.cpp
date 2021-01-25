#include "Character.h"

Character::Character(string type, string character)
{
	setTokenType(type);
	setTokenValue(character);
}

string Character::getTokenType()
{
	return ((Token*) this)->getTokenType();
}
string Character::getTokenValue()
{
	return ((Token*) this)->getTokenValue();
}