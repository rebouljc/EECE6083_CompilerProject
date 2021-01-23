#pragma once

#include <set>
#include <string>

using namespace std;

class Token
{
public:
	Token(string tokenType, string tokenValue);
	bool operator == (Token* tok);
private:
	string tokenType;
	string tokenValue;
	string tokenLineNumber;
	int tokenOccurrence;
	
};