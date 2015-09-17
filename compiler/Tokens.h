#ifndef _TokenType_H_
#define _TokenType_H_

#include <sstream>

enum TokenType {
	T_EOF = 0,
	T_UNKNOWN = 1,
	T_SEMICOLON = 2,
	T_IDENTIFIER = 3,
	T_INT = 4,
	T_DIGIT = 5,
	T_LPAREN = 6,
	T_RPAREN = 7,
	T_DISJUNCTION = 8,
	T_CONJUNCTION = 9,
	T_OP_ASSIGN = 10,
	T_LBRACE = 11,
	T_RBRACE = 12,
	T_VOID = 13,
	T_COMMA = 14,
	T_OP_UNARY_ADD = 15,
	T_OP_UNARY_SUBSTRACT = 16,
	T_OP_BINARY_ADD = 17,
	T_OP_BINARY_SUBSTRACT = 18,
	T_STAR = 19,
	T_OP_DIVIDE = 20,
	T_RETURN = 21,
	T_ASM = 22,
	T_STRING = 23,
	T_CHAR = 24,
	T_OP_EQUAL = 25,
	T_WHILE = 26,
	T_OP_NOTEQUAL = 27,
	T_OP_GREATER = 28,
	T_OP_LESS = 29,
	T_OP_GREATEREQUAL = 30,
	T_OP_LESSEQUAL = 31,
	T_IF = 32,
	T_ELSE = 33,
	T_LBRACKET = 34,
	T_RBRACKET = 35,
	T_GLOBAL = 36,
	T_MOD = 37,
	T_VAR = 38,
	T_CONST = 39
};

struct Token {
	TokenType		_type;
	std::string		_identifier;

	union {
		int				uintvalue;
		bool			boolvalue;
		char			*stringvalue;
		char			charvalue;
		float			floatvalue;
	} _value;

	Token() {
		_type = TokenType::T_UNKNOWN;
		//_value.boolvalue = 0;
		_value.uintvalue = 0;
	}

	TokenType GetType()
	{
		return (TokenType)_type;
	}

	std::string getStringValue()
	{
		switch (_type)
		{
		case T_IDENTIFIER:
			return "IDENTIFIER " + _identifier;
			break;
		case T_DIGIT:
			return std::to_string(_value.uintvalue);
			break;
		case T_DISJUNCTION:
			return "DISJUNCTION"; break;
		case T_CONJUNCTION:
			return "CONJUNCTION"; break;
		case T_LPAREN:
			return "("; break;
		case T_RPAREN:
			return ")"; break;
		case T_OP_ASSIGN:
			return "="; break;
		case T_OP_BINARY_ADD:
			return "+"; break;
		case T_OP_BINARY_SUBSTRACT:
			return "-"; break;
		case T_STAR:
			return "*"; break;
		case T_OP_DIVIDE:
			return "/"; break;
		default: return "?";
		}
	}
};

#endif