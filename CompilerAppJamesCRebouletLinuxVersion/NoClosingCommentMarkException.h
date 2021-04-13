#pragma once
struct NoClosingCommentMarkException
{


	const char* what() const throw ()
	{
		return "Unrecoverable Lexer Error: Illegal Comment Closing/Opening: Missing either (* or /) on /* or */ Comment.\n  You also could have left out a space before the comment close. Comments must be surrounded by /*...*/ - on line number: ";
	}

	
};