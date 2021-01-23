#pragma once


#include <set>
#include <vector>
#include <string>
#include "Token.h"
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

   bool matchSingleCharacter(string character);
   bool matchReservedWord();
   void readFile();
   void readCharacterFromFile(string filename);
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

