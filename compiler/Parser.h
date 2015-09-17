#ifndef _PARSER_H_
#define _PARSER_H_

#include <list>
#include <vector>
#include <string>
#include <stack>
#include "tree.h"
#include "lexer.h"

class Parser
{
public:
	Parser(std::vector<Token> tokens);
	virtual ~Parser();

	void parse();
	TreeNode* getAST();
	Token getNext();
	Token getCurrent();
	TokenType currentType();
	void printTree(TreeNode* node);

	TreeNode* rootNode;
	TreeNode* parse_compilation_unit();
	TreeNode* parse_function_declaration();
	TreeNode* parse_function_header();
	TreeNode* parse_function_returntype();
	TreeNode* parse_function_param_list();
	TreeNode* parse_param();
	TreeNode* parse_block();
	TreeNode* parse_statement();
	TreeNode* parse_assembly();
	TreeNode* parse_declaration_statement();
	TreeNode* parse_expression();
	TreeNode* parse_initializer();
	TreeNode* parse_expression_relation();
	TreeNode* parse_expression_addition();
	TreeNode* parse_expression_multiplication();
	TreeNode* parse_factor();
	TreeNode* parse_unary1();
	TreeNode* parse_unary2();
	TreeNode* parse_function_args();

	std::vector<Token> m_tokenList;
	unsigned int m_currentTokenIndex;
};

#endif