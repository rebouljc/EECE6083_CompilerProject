#pragma once

struct IdentifierBeginsWithNumberException
{


	const char* what() const throw ()
	{
		return "Identifier Exception: Identifier can't begin with a number.  Must begin with letter - on line ";
	}


};