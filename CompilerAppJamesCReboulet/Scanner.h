#pragma once


#include <set>
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
   
   set<pair<string, Token*>> reserved;
   set<pair<string, Token*>> punctuation;
   set<pair<string, Token*>> assignment;
   set<pair<string, Token*>> arithOperator;
   set<pair<string, Token*>> relationOperator;
   set<pair<string, Token*>> booleanOperator;


};

