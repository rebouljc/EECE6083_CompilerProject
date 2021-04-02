#pragma once

struct ArithOperatorsAreNotAValidTypeException
{

	const char* what() const throw ()
	{
		return "\nParser/Semantic Error (Arithmetic Type Error):\n The current identifiers must be of either type integer or type float -- on line ";
	}


};