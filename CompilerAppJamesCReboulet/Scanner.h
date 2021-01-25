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

   //create methods
   void createDigitCharacter(char character);
   void createLetterCharacter(char character);
   void createPunctuationToken();
   void createAssignmentToken();
   void createArithOperatorToken();
   void createRelationOperatorToken();
   void createBooleanOperatorToken();
   void createReservedWordToken();
   void createIdentifierToken();
   void createStringLiteralToken();
 
   //read character method

   char readCharacterFromFile(ifstream* filename);

   //search methods

   Token* searchPunctuationList(string character);
   Token* searchAssignmentList(string character);
   Token* searchArithOperatorList(string character);
   Token* searchRelationOperatorList(string character);
   Token* searchBooleanOperatorList(string character);

   Token* searchSingleCharacterLists(string character);

   bool matchReservedWord(string matchString); //Calls createReservedWordToken() if true;
   bool matchPunctuation(string character);
   void readFile();
   
   void reportError();
   void reportWarning();

   //Other methods - if not a digit or a number
   void performOtherAction();

   
   set<pair<string, Token*>> reserved;
   set<pair<string, Token*>> punctuation;
   set<pair<string, Token*>> assignment;
   set<pair<string, Token*>> arithOperator;
   set<pair<string, Token*>> relationOperator;
   set<pair<string, Token*>> booleanOperator;
   vector<Token*> storedTokens;
   vector<Character*> storedCharacters;


};

