#pragma once

struct NoStringsAllowedInRelationOperatorsException
{

	const char* what() const throw ()
	{
		return "\nParser/Semantic Error (Relational Operator Type Error):\n The current operands using any relational operator besides \"==\" or \"!=\" cannot be of type \"string\" -- on line ";
	}


};