#pragma once


struct MainCompilerIntermediateCodeGenerationException
{


	const char* what() const throw ()
	{
		return "\nThe current compile operation has resulted in one or more errors, which need to be fixed before Intermediate-Code Generation can occur.\nUnfortunately, Mama can't help you with this one!";
	}


};