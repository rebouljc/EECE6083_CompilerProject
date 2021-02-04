#pragma once
struct IllegalIdentifierException
{


	const char* what() const throw ()
	{
		return "Identifier Has Illegal Character: Identifier contains one of the following illegal characters: ~ , !, ?, @, ', `, $, %, #  - on line ";
	}


};