#pragma once

struct IdentifierNotDeclaredException
{


	const char* what() const throw ()
	{
		return "The identifier is being used but has not been previously declared either locally or globally - on line ";
	}


};