#pragma once
struct ArrayIndexNotAnIntegerLiteralException
{


	const char* what() const throw ()
	{
		return "Parser/Semantic Error (Array Index Not Integer): An array index must be of type INTEGER_LITERAL - on line: ";
	}


};