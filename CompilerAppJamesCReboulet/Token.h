#pragma once

#include <set>
#include <string>

using namespace std;

class Token
{
public:
	Token();
	Token(string tokenType, string tokenValue);
	bool operator == (Token* tok);
protected:
	string tokenType;
	string tokenValue;
	string tokenLineNumber;
	int tokenOccurrence;
	void setTokenOccurrence(int occurrence);
	void setTokenLineNumber(string lineNumber);
	
};