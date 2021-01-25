#pragma once


#include <set>
#include <vector>
#include <string>
#include "Token.h"
#include <fstream>
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
   void createPunctuationToken();
   void createAssignmentToken();
   void createArithOperatorToken();
   void createRelationOperatorToken();
   void createBooleanOperatorToken();
   void createReservedWordToken();
   void createIdentifierToken();
   void createStringLiteralToken();
 
   //read character method

   string readCharacterFromFile(ifstream* filename);

   //search methods

   Token* searchPunctuationList(string character);
   Token* searchAssignmentList(string character);
   Token* searchArithOperatorList(string character);
   Token* searchRelationOperatorList(string character);
   Token* searchBooleanOperatorList(string character);

   Token* searchSingleCharacterLists(string character);

   bool matchReservedWord(string matchString); //Calls createReservedWordToken() if true;
   bool matchLetter(string character);
   bool matchDigit(string character);
   bool matchPunctuation(string character);
   void readFile();
   
   void reportError();
   void reportWarning();

   
   set<pair<string, Token*>> reserved;
   set<pair<string, Token*>> punctuation;
   set<pair<string, Token*>> assignment;
   set<pair<string, Token*>> arithOperator;
   set<pair<string, Token*>> relationOperator;
   set<pair<string, Token*>> booleanOperator;
   vector<Token*> storedTokens;


};

