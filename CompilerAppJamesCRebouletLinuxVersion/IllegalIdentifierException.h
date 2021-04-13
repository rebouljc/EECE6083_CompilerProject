#pragma once
struct IllegalIdentifierException
{


	const char* what() const throw ()
	{
		return "Lexer Error: Identifier Has Illegal Character: Identifier contains one of the following illegal characters: ~ , !, ?, @, ', `, $, %, #  - on line ";
	}


};