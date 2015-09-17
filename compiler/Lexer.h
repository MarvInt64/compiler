#ifndef __LEXER_H_
#define __LEXER_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "tokens.h"

class Lexer
{
public:
	Lexer();
	Lexer(const std::string& _input);
	virtual ~Lexer();

	std::vector<Token> LexicalAnalyisis();

	void		setInput(const std::string& _input);
	void		next();
	char		getCurrentChar();

	Token		getTokenProto();
	Token		getToken();
	Token		getCurrentToken();

private:
	int			m_currentCharPos;
	std::string m_inputString;
	Token		m_currentToken;
};

#endif