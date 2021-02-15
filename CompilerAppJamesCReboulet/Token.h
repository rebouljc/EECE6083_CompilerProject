#pragma once

#include <vector>
#include <string>



using namespace std;

class Token
{
public:
	Token();
	
	Token(int tokLineNumber);
	Token(string tokenType, string tokenValue, int tokenLineNumber);
	Token(string tokenType, string tokenValue);
	Token(Token* token, int tokLineNumber);
	Token(string tokenType, double numberValue);
	Token(string tokenType, double numberValue, int tokenLineNumber);
	bool operator == (Token* tok);
	string getTokenType();
	string getTokenValue();
	void setTokenType(string type);
	void setTokenValue(string value);
	void setTokenIsPeriodStatus(bool setting);
	bool getIsPeriodStatus();
	void setDoubleNumberTokenValue(double value);
	double getIntegerDoubleNumberTokenValue();
	int getTokenLineNumber();
	void setTokenLineNumber(int tokLineNumber);
	
	
protected:
	string tokenType;
	string tokenValue;
	double integerNumberTokenValue;
	int tokenLineNumber;
	int tokenOccurrence;
	void setTokenOccurrence(int occurrence);
	bool isPeriod = false;
	
	
	
	
};