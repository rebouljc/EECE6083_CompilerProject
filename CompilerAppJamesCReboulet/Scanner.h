#pragma once


#include <set>
#include <string>
#include "Token.h"
using namespace std;
class Scanner
{
public:
private:
    set<pair<string, Token>> reserved;
};