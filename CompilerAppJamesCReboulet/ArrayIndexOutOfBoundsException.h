#pragma once
struct ArrayIndexOutOfBoundsException
{


	const char* what() const throw ()
	{
		return "Parser/Semantic Error (Array Index Out of Bounds): Array Index is out of Bounds -- on line: ";
	}


};