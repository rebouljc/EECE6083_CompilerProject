#pragma once
struct NoPeriodAtEndOfProgramException
{


	const char* what() const throw ()
	{
		return "Lexer Error: Program Must End With A Period. - on line ";
	}


};