#pragma once



struct StringLiteralException
{
	
	
	const char* what() const throw ()
	{
		return "Unrecoverable Lexer Error: String Literal Exception: Missing quotation \" marks on String Literal - on Line Number: ";
	}
	

};