#pragma once
struct MainCompileErrorException
{


	const char* what() const throw ()
	{
		return "\nThe current compile operation has resulted in errors.  Fix them and stop making mistakes, and Mama can't help you either.";
	}


};