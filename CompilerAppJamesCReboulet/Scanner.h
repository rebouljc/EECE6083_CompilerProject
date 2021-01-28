#pragma once


#include <set>
#include <vector>
#include <string>
#include "Token.h"
#include <fstream>
#include "Character.h"
using namespace std;

class Scanner
{
   public:
	   Scanner();
	   

   private:
   void populateReservedList();
   void populatePunctuationList();
   void populateAssignmentList();
   void populateArithOperatorList();
   void populateRelationOperatorList();
   void populateBooleanOperatorList();
   void populateWhitespaceSymbolsList();

   //create methods
   void createDigitCharacter(char character);
   void createLetterCharacter(char character);
   void createSingleCharacterToken(Token* token);
   void createAssignmentToken();
   void createArithOperatorToken();
   void createRelationOperatorToken();
   void createBooleanOperatorToken();
   void createReservedWordToken(Token* tokenToAdd);
   void createIdentifierToken();
   void createStringLiteralToken();
   void createNumberToken(string type, double value);
 
   //read character method

   char readCharacterFromFile(ifstream* filename);
   char peekNextCharacterInFile(ifstream* inputStream);

   //search methods

   Token* searchPunctuationList(string character);
   Token* searchAssignmentList(string character, ifstream* input);
   Token* searchArithOperatorList(string character);
   Token* searchRelationOperatorList(string character, ifstream* input);
   Token* searchBooleanOperatorList(string character);
   Token* searchReservedWordList(string character);
   Token* searchSingleCharacterLists(string character, ifstream* input);

   //match methods

   void matchReservedWord(); //Calls createReservedWordToken() if true;
   bool matchIdentifier();
   void matchNumber();
   void matchLetter();
   void matchStringLiteral();
   void otherActionMatchNotReservedWord();

   //initial readFileMethod()

   void readFile(ifstream* input);
   
   void reportError();
   void reportWarning();

   //Other methods - if not a digit or a number

   void performOtherAction(ifstream* input, char character);
   bool isWhitespace(char character);
   double computeFloatingPointResult(vector<int>* inputVector, double input, double exponent);

   
   set<pair<string, Token*>> reserved;
   set<pair<string, Token*>> punctuation;
   set<pair<string, Token*>> assignment;
   set<pair<string, Token*>> arithOperator;
   set<pair<string, Token*>> relationOperator;
   set<pair<string, Token*>> booleanOperator;
   vector<char> whitespaceSymbols;
   vector<Token*> storedTokens;
   vector<Character*> storedCharacters;


};

