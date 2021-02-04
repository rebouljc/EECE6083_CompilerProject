#pragma once
struct NoClosingCommentMarkException
{


	const char* what() const throw ()
	{
		return "Illegal Comment Closing/Opening: Missing either (* or /) on /* or */ Comment.\n  Comments must be surrounded by /*...*/ - close to line number: ";
	}

	
};