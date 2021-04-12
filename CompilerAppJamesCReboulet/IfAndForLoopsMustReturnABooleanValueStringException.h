#pragma once

struct IfAndForLoopsMustReturnABooleanValueException
{

	const char* what() const throw ()
	{
		return "\nParser/Semantic Error (If-Statement/For-Loop Non-Boolean-Value Error):\n If Statements and For-Loops must return a boolean value. Strings and string-literals and floats are not permitted as single expressions. -- on line ";
	}


};