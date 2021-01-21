#pragma once

#include <set>
#include <string>

using namespace std;

class Token
{
public:
	Token(string tokenType, string tokenValue);
private:
	string tokenType;
	string tokenValue;
	
};