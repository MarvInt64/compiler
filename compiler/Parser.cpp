
#include "Parser.h"

Parser::Parser(std::vector<Token> tokens) {
	m_tokenList = tokens;
	m_currentTokenIndex = 0;
}

Parser::~Parser() {
	delete rootNode;
}

TreeNode* Parser::getAST()
{
	return rootNode;
}

Token Parser::getCurrent()
{
	if (m_currentTokenIndex >= m_tokenList.size())
	{
		Token t;
		t._type = TokenType::T_EOF;
		return t;
	}

	return m_tokenList[m_currentTokenIndex];
}

Token Parser::getNext()
{
	if (m_currentTokenIndex > m_tokenList.size()-1)
	{
		Token t;
		t._type = TokenType::T_EOF;
		return t;
	}

	return m_tokenList[m_currentTokenIndex++];
}

TokenType Parser::currentType()
{
	return getCurrent().GetType();
}

void Parser::printTree(TreeNode* node) 
{
	std::cout << std::endl << std::endl;
	if (node == NULL)
		if (rootNode != NULL)
			node = rootNode;
		else
			std::cout << "ooops!" << std::endl;

	node->printNode(0);
	std::cout << std::endl;
	std::cout << std::endl;
}

void Parser::parse() 
{
	rootNode = new TreeNode(NodeType::NODE_COMPILATION_UNIT);

	while (currentType() != TokenType::T_EOF)
	{
		rootNode->addChild(parse_compilation_unit());
	}
}

TreeNode* Parser::parse_compilation_unit()
{
	if (currentType() == T_VOID || currentType() == T_INT || currentType() == T_CHAR || currentType() == T_IDENTIFIER)
	{
		return parse_function_declaration();
	}

	return nullptr;
}

TreeNode* Parser::parse_function_declaration()
{
	TreeNode* node = new TreeNode(NodeType::NODE_FUNCTIONDECL);
	node->addChild(parse_function_header());

	if (currentType() == TokenType::T_SEMICOLON)
	{
		getNext();
	}
	else if (currentType() == TokenType::T_LBRACE)
	{
		node->addChild(parse_block());
	}
	else
	{
		std::cout << "Expection function definition block after function header!" << std::endl;
	}

	return node;
}


TreeNode* Parser::parse_function_header()
{
	TreeNode* functionHeaderNode = new TreeNode(NodeType::NODE_FUNCTIONHEADER);
	functionHeaderNode->addChild(parse_function_returntype());

	if (currentType() == TokenType::T_IDENTIFIER)
	{
		functionHeaderNode->addChild(new TreeNode(NodeType::NODE_IDENTIFIER, getCurrent()));

		getNext();

		if (getCurrent().GetType() == TokenType::T_LPAREN)
		{
			getNext();
			functionHeaderNode->addChild(parse_function_param_list());
		}
		else
		{
			std::cout << "Expecting '(' after function identifier." << std::endl;
		}
	}
	else
	{
		std::cout << "Expecting function identifier." << std::endl;
	}

	return functionHeaderNode;
}

TreeNode* Parser::parse_function_returntype()
{
	TreeNode* node = new TreeNode(NodeType::NODE_RETURNTYPE);
	node->addChild(new TreeNode(getNodeFromToken( getCurrent() )));
	getNext();

	return node;
}

TreeNode* Parser::parse_function_args() {
	TreeNode* node;

	getNext();
	node =new TreeNode(NodeType::NODE_FUNCARGS);

	bool _loop = false;

	if (currentType() != TokenType::T_RPAREN)
	{
		do {
			TreeNode* nodeExpr = parse_expression();
			if (nodeExpr->m_nodeType == NodeType::NODE_FACTOR)
				nodeExpr = nodeExpr->getChild(0);

			node->addChild(nodeExpr);

			_loop = (currentType() == TokenType::T_COMMA);

			if (_loop)
				getNext();
		} while (_loop);
	}

	if (currentType() != TokenType::T_RPAREN)
	{
		std::cout << "Error: Expecting ')' after argument list!" << std::endl;
	}

	getNext();

	return node;
}

TreeNode* Parser::parse_param()
{
	TreeNode* node = new TreeNode(NodeType::NODE_PARAM);

	if (currentType() == T_INT || currentType() == T_CHAR)
	{
		node->addChild(new TreeNode(getNodeFromToken(getCurrent())));
	}
	else
		std::cout << "Expecting valid data type in parameter list" << std::endl;


	getNext();
	//TreeNode* nodeReference = parse_reference();
	//getNext();

	if (currentType() != T_IDENTIFIER)
	{
		std::cout << "Expecting identifier in param list" << std::endl;
		exit(0);
	}

	node->addChild( new TreeNode(NodeType::NODE_IDENTIFIER, getCurrent()));
	//ast->AddChild(node, nodeReference);
	getNext();
	//ast->AddChild(node, parse_dimension_block());

	return node;
}

TreeNode* Parser::parse_function_param_list()
{
	TreeNode* node = new TreeNode(NodeType::NODE_PARAMLIST);

	if (currentType() == TokenType::T_VOID || currentType() == TokenType::T_RPAREN)
	{
		node->addChild(new TreeNode(NodeType::NODE_VOID));
		getNext();
		return node;
	}

	TokenType tokenType = TokenType::T_UNKNOWN;
	bool loop = true;

	while (loop)
	{
		tokenType = currentType();

		node->addChild(parse_param());
		loop = (currentType() == (T_COMMA));
		getNext();
	}

	return node;
}

TreeNode* Parser::parse_block()
{
	TreeNode* node = new TreeNode(NodeType::NODE_BLOCK);

	//getNext();

	if (currentType() == TokenType::T_LBRACE)
	{
		getNext();

		while (currentType() != TokenType::T_RBRACE)
		{
			if (currentType() == TokenType::T_ASM)
			{
				node->addChild(parse_assembly());
			}
			else
			{
				node->addChild(parse_statement());
			}
		}
	}
	else
	{
		std::cout << "A code block has to start with '{'." << std::endl;
	}

	getNext();

	return node;
}


TreeNode* Parser::parse_assembly()
{
	TreeNode* node = new TreeNode(NodeType::NODE_ASSEMBLY);
	TreeNode *result = NULL;

	getNext();
	if (currentType() == TokenType::T_LBRACE)
	{
		while (currentType() != TokenType::T_RBRACE)
		{
			getNext();
			if (currentType() == TokenType::T_STRING)
				node->addChild(new TreeNode(NodeType::NODE_ASSEMBLY_LINE, getCurrent()));
		}
	}
	else
	{
		std::cout << "Error: Inline assembly block must begin with '{'!" << std::endl;
	}

	getNext();

	return node;
}


TreeNode* Parser::parse_statement()
{
	TreeNode* node = new TreeNode(NodeType::NODE_STATEMENT);

	/*if (currentType() == TokenType::T_IDENTIFIER)
	{

	} 
	else */
	if (currentType() == TokenType::T_SEMICOLON)
	{
		getNext();
		return nullptr;
	}
	else if (currentType() == TokenType::T_WHILE)
	{

	}
	else if (currentType() == TokenType::T_INT)
	{
		node->addChild(parse_declaration_statement());
	}
	else
	{
		node->addChild(parse_expression());
	}

	return node;
}

TreeNode* Parser::parse_declaration_statement()
{
	TreeNode* node = new TreeNode(NodeType::NODE_DECLARATION);

	node->addChild(new TreeNode(getNodeFromToken( getCurrent())) );

	getNext();

	if (currentType() == TokenType::T_IDENTIFIER)
	{
		node->addChild(new TreeNode(NodeType::NODE_IDENTIFIER, getCurrent()));
		getNext();
		node->addChild(parse_initializer());
	}
	else
	{
		std::cout << "Expecting identifier after type specifier!" << std::endl;
	}

	return node;
}

TreeNode* Parser::parse_expression()
{
	TreeNode* node = parse_expression_relation();
	TreeNode* opNode = nullptr;

	if (currentType() != TokenType::T_OP_ASSIGN)
	{
		//getNext();
		return node;
	}
	else
	{
		opNode =new TreeNode(getNodeFromToken(getCurrent()));

		getNext();

		opNode->addChild(node);
		opNode->addChild(parse_expression());

		return opNode;
	}

	return opNode;
}

TreeNode* Parser::parse_initializer()
{
	TreeNode* node = nullptr;

	if (currentType() == TokenType::T_OP_ASSIGN)
	{
		TreeNode* expressionNode = parse_expression();

		if (expressionNode != nullptr)
		{
			node = new TreeNode(NodeType::NODE_INITIALIZER);
			node->addChild(expressionNode);
		}
	} 

	return node;
}

TreeNode* Parser::parse_expression_relation()
{
	TreeNode* node =  parse_expression_addition();
	TreeNode* opNode = nullptr;

	while (
		currentType() == TokenType::T_OP_GREATER ||
		currentType() == TokenType::T_OP_GREATEREQUAL ||
		currentType() == TokenType::T_OP_LESS ||
		currentType() == TokenType::T_OP_LESSEQUAL
		)
	{
		opNode = new TreeNode(getNodeFromToken(getCurrent()));
		opNode->addChild(node);
		
		getNext();

		opNode->addChild(parse_expression_addition());
		node = opNode;
	}

	return node;
}

TreeNode* Parser::parse_expression_addition()
{
	TreeNode* node;
	TreeNode* opNode;

	node = parse_expression_multiplication();

	while (currentType() == TokenType::T_OP_BINARY_ADD || currentType() == TokenType::T_OP_BINARY_SUBSTRACT)
	{
		opNode = new TreeNode(getNodeFromToken(getCurrent()), getCurrent());
		opNode->addChild(node);
		
		getNext();
		opNode->addChild(parse_expression_multiplication());
		node = opNode;
	}

	return node;
}

TreeNode* Parser::parse_expression_multiplication() {
	TreeNode* child;
	TreeNode* op;

	child = parse_unary2();

	while (currentType() == TokenType::T_STAR || currentType() == TokenType::T_OP_DIVIDE || currentType() == TokenType::T_MOD)
	{
		op = new TreeNode(getNodeFromToken(getCurrent()), getCurrent());
		op->addChild(child);

		getNext();

		op->addChild(parse_unary2());
		child = op;
	}

	return child;
}

TreeNode* Parser::parse_unary1() 
{
	TreeNode* node;
	TreeNode* child;

	node = parse_factor();

	while (currentType() == TokenType::T_LPAREN || currentType() == TokenType::T_LBRACKET)
	{
		if (currentType() == T_LPAREN)
		{
			child = node;
			node = new TreeNode(NodeType::NODE_FUNCCALL);
			node->addChild(child->getChild(0)); //getChild because we skip the NODE_FACTOR

			if (currentType() != TokenType::T_RPAREN)
			{
				TreeNode* nodeArgs = parse_function_args();
				if (nodeArgs->m_children.size() > 0)
					node->addChild(nodeArgs);
			}
		}

		if (currentType() == TokenType::T_LBRACKET)
		{
			getNext();

			child = node;
			node = new TreeNode(NodeType::NODE_INDEXER);
			node->addChild(child);
			node->addChild(parse_expression());

			if (currentType() != TokenType::T_RBRACKET)
			{
				std::cout << "Error: Expecting ']' after array index expression." << std::endl;
				exit(0);
			}
			getNext();
		}
	}

	return node;
}

TreeNode* Parser::parse_unary2() {

	TreeNode* node = nullptr;// = parse_unary1();

	if (currentType() == TokenType::T_OP_BINARY_ADD || currentType() == TokenType::T_OP_BINARY_SUBSTRACT)
	{
		switch (currentType())
		{
		case T_OP_BINARY_ADD:
			node = new TreeNode(NodeType::NODE_UNARY_ADD);
			break;
		case T_OP_BINARY_SUBSTRACT:
			node = new TreeNode(NodeType::NODE_UNARY_SUBSTRACT);
			break;
		}

		getNext();
		node->addChild(parse_unary2());
	}
	else
		node = parse_unary1();

	return node;
}

TreeNode* Parser::parse_factor()
{
	TreeNode* node = new TreeNode(NodeType::NODE_FACTOR);

	if (currentType() == TokenType::T_LPAREN)
	{
		getNext();
		node->addChild(parse_expression());
		getNext();
	}
	else if (currentType() == TokenType::T_IDENTIFIER)
	{
		node->addChild(new TreeNode(NodeType::NODE_IDENTIFIER, getCurrent()));
		getNext();
	}
	else if (
		currentType() == TokenType::T_DIGIT ||
		currentType() == TokenType::T_STRING ||
		currentType() == TokenType::T_CHAR
		)
	{
		switch (currentType())
		{
		case TokenType::T_DIGIT: node->addChild(new TreeNode(NodeType::NODE_DIGIT, getCurrent())); break;
			
		}

		getNext();
	}

	if (node->m_children.size() <= 0)
		node = nullptr;

	return node;
}