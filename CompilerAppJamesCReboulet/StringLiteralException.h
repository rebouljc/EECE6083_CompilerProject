#pragma once



struct StringLiteralException
{
	
	
	const char* what() const throw ()
	{
		return "String Literal Exception: Missing quotation \" marks on String Literal - on Line Number: ";
	}
	

};