#pragma once
struct GlobalIdentifierIsNotUniqueException
{


	const char* what() const throw ()
	{
		return "Parser/Semantic Error (Non-Unique Identifier):\n The current identifier has already been declared globally and is being redeclared, which is not permitted - on line: ";
	}


};