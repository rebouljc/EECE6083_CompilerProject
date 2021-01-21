#include "Scanner.h"

Scanner::Scanner()
{
	this->populateReservedList();
	this->populatePunctuationList();
	this->populateAssignmentList();
	this->populateArithOperatorList();
	this->populateRelationOperatorList();
	this->populateBooleanOperatorList();
}
void Scanner::populateReservedList()
{
	
	this->reserved.insert(make_pair("program", new Token("RESERVED_WORD", "program")));
	this->reserved.insert(make_pair("is", new Token("RESERVED_WORD", "is")));
	this->reserved.insert(make_pair("begin", new Token("RESERVED_WORD", "begin")));
	this->reserved.insert(make_pair("end", new Token("RESERVED_WORD", "end")));
	this->reserved.insert(make_pair("global", new Token("RESERVED_WORD", "global")));
	this->reserved.insert(make_pair("procedure", new Token("RESERVED_WORD", "procedure")));
	this->reserved.insert(make_pair("variable", new Token("RESERVED_WORD", "variable")));
	this->reserved.insert(make_pair("type", new Token("RESERVED_WORD", "type")));
	this->reserved.insert(make_pair("integer", new Token("RESERVED_WORD", "integer")));
	this->reserved.insert(make_pair("float", new Token("RESERVED_WORD", "float")));
	this->reserved.insert(make_pair("string", new Token("RESERVED_WORD", "string")));
	this->reserved.insert(make_pair("bool", new Token("RESERVED_WORD", "bool")));
	this->reserved.insert(make_pair("enum", new Token("RESERVED_WORD", "enum")));
	this->reserved.insert(make_pair("if", new Token("RESERVED_WORD", "if")));
	this->reserved.insert(make_pair("then", new Token("RESERVED_WORD", "then")));
	this->reserved.insert(make_pair("else", new Token("RESERVED_WORD", "else")));
	this->reserved.insert(make_pair("for", new Token("RESERVED_WORD", "for")));
	this->reserved.insert(make_pair("return", new Token("RESERVED_WORD", "return")));
	this->reserved.insert(make_pair("not", new Token("RESERVED_WORD", "not")));
	this->reserved.insert(make_pair("true", new Token("RESERVED_WORD", "true")));
	this->reserved.insert(make_pair("false", new Token("RESERVED_WORD", "false")));
}

void Scanner::populatePunctuationList()
{
	this->punctuation.insert(make_pair(".", new Token("PUNCTUATION", ".")));
	this->punctuation.insert(make_pair(";", new Token("PUNCTUATION", ";")));
	this->punctuation.insert(make_pair(",", new Token("PUNCTUATION", ",")));
	this->punctuation.insert(make_pair("(", new Token("PUNCTUATION", "(")));
	this->punctuation.insert(make_pair(")", new Token("PUNCTUATION", ")")));
	this->punctuation.insert(make_pair("{", new Token("PUNCTUATION", "{")));
	this->punctuation.insert(make_pair("}", new Token("PUNCTUATION", "}")));
	this->punctuation.insert(make_pair("[", new Token("PUNCTUATION", "[")));
	this->punctuation.insert(make_pair("]", new Token("PUNCTUATION", "]")));
	this->punctuation.insert(make_pair("-", new Token("PUNCTUATION", "-")));
	this->punctuation.insert(make_pair("\"", new Token("PUNCTUATION", "\"")));
	this->punctuation.insert(make_pair("^\"", new Token("PUNCTUATION", "^\"")));
	
}

void Scanner::populateAssignmentList()
{
    this->assignment.insert(make_pair(":=", new Token("ASSIGNMENT", ":=")));
	
}

void Scanner::populateArithOperatorList()
{
	this->arithOperator.insert(make_pair("+", new Token("ARITH_OPERATOR", "+")));
	this->arithOperator.insert(make_pair("-", new Token("ARITH_OPERATOR", "-")));
	this->arithOperator.insert(make_pair("*", new Token("ARITH_OPERATOR", "*")));
	this->arithOperator.insert(make_pair("/", new Token("ARITH_OPERATOR", "/")));
}

void Scanner::populateRelationOperatorList()
{
	this->relationOperator.insert(make_pair("<", new Token("RELATION_OP", "<")));
	this->relationOperator.insert(make_pair(">", new Token("RELATION_OP", ">")));
	this->relationOperator.insert(make_pair("<=", new Token("RELATION_OP", "<=")));
	this->relationOperator.insert(make_pair(">=", new Token("RELATION_OP", ">=")));
	this->relationOperator.insert(make_pair("==", new Token("RELATION_OP", "==")));
	this->relationOperator.insert(make_pair("!=", new Token("RELATION_OP", "!=")));
}

void Scanner::populateBooleanOperatorList()
{
	this->booleanOperator.insert(make_pair("&", new Token("BOOLEAN_OP", "&")));
	this->booleanOperator.insert(make_pair("|", new Token("BOOLEAN_OP", "|")));
}