#pragma once
#include <string>
#include "Token.h"
using namespace std;

class Character:Token
{
public:
	Character(string type, string character);
	string getTokenType();
	string getTokenValue();

	
private:
	

};