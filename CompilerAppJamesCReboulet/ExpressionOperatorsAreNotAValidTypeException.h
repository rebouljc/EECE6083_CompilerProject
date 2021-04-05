#pragma once

struct ExpressionOperatorsAreNotAValidTypeException
{

	const char* what() const throw ()
	{
		return "\nParser/Semantic Error (Expression-Bitwise-Operator Type Error):\n The current operands using bitwise & or | must be of either type integer or of type bool -- on line ";
	}


};