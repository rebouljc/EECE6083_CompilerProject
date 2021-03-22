#pragma once
struct MainCompileErrorException
{


	const char* what() const throw ()
	{
		return "\nThe current compile operation has resulted in one or more unrecoverable errors, which need to be fixed before any further errors can be detected.\nUnfortunately, I can't help you and calling Mom probably wouldn't work either!";
	}


};