#pragma once

struct IllegalRelationalOperatorComparisonOfIntegerFloatWithStringException
{

	const char* what() const throw ()
	{
		return "\nParser/Semantic Error (Relational Operator Illegal String Comparison Type Error):\n Comparing a variable of type \"string\" or a \"STRING_LITERAL\" with either a floating point value or an integer value is not permitted -- on line ";
	}


};