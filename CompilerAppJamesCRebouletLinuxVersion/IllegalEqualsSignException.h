#pragma once
struct IllegalEqualsSignException
{


	const char* what() const throw ()
	{
		return "Lexer Error: Illegal Character: An equals sign '=' by itself is not permitted.\nIt must be \":=\" for assignment or \"==\" for relation\nNeither are ~ , !, ?, @, ', `, $, %, # by themselves -on line ";
	}


};