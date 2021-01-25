#pragma once

#include <set>
#include <string>

using namespace std;

class Token
{
public:
	Token();
	Token(string tokenType, string tokenValue);
	Token(Token* token);
	bool operator == (Token* tok);
	string getTokenType();
	string getTokenValue();
	void setTokenType(string type);
	void setTokenValue(string value);
protected:
	string tokenType;
	string tokenValue;
	string tokenLineNumber;
	int tokenOccurrence;
	void setTokenOccurrence(int occurrence);
	void setTokenLineNumber(string lineNumber);
	
};