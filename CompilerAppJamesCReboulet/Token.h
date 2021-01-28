#pragma once

#include <vector>
#include <string>


using namespace std;

class Token
{
public:
	Token();
	Token(string tokenType, string tokenValue);
	Token(Token* token);
	Token(string tokenType, double numberValue);
	bool operator == (Token* tok);
	string getTokenType();
	string getTokenValue();
	void setTokenType(string type);
	void setTokenValue(string value);
	void setTokenIsPeriodStatus(bool setting);
	bool getIsPeriodStatus();
	void setDoubleNumberTokenValue(double value);
	double getIntegerDoubleNumberTokenValue();
	
protected:
	string tokenType;
	string tokenValue;
	double integerNumberTokenValue;
	string tokenLineNumber;
	int tokenOccurrence;
	void setTokenOccurrence(int occurrence);
	void setTokenLineNumber(string lineNumber);
	bool isPeriod = false;
	
	
};