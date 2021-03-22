#pragma once
#include <string>

struct IdentifierNotDeclaredException
{

	const char* what() const throw ()
	{
		return "Parser/Semantic Error (Forward Reference):\n The identifier: is being used but has not been previously declared either locally or globally - on line ";	
	}

	
};