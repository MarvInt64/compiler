#ifndef _TREE_H_
#define _TREE_H_

#include <list>
#include <vector>
#include <string>
#include <iostream>
#include "tokens.h"

enum NodeType {
	NODE_COMPILATION_UNIT = 0,
	NODE_EXPRESSION,
	NODE_IDENTIFIER,
	NODE_OP_CONJUNCTION,
	NODE_OP_DISJUNCTION,
	NODE_DECL,
	NODE_DIGIT,
	NODE_GLOBAL,
	NODE_FUNCTION,
	NODE_FUNCTIONHEADER,
	NODE_VOID,
	NODE_RETURNTYPE,
	NODE_INT,
	NODE_PARAMLIST,
	NODE_PARAM,
	NODE_BLOCK,
	NODE_STATEMENT,
	NODE_FACTOR,
	NODE_DECLARATION,
	NODE_OP_ASSIGN,
	NODE_FUNCTIONDECL,
	NODE_UNARY_ADD,
	NODE_UNARY_SUBSTRACT,
	NODE_BINARY_ADD,
	NODE_BINARY_SUBSTRACT,
	NODE_FUNCCALL,
	NODE_FUNCARGS,
	NODE_MULTIPLICATION,
	NODE_DIVISION,
	NODE_RETURN,
	NODE_ASSEMBLY,
	NODE_ASSEMBLY_LINE,
	NODE_STRING,
	NODE_REFERENCE,
	NODE_CHAR,
	NODE_EQUALITY,
	NODE_WHILE,
	NODE_INEQUALITY,
	NODE_GREATER,
	NODE_GREATEREQUAL,
	NODE_LESS,
	NODE_LESSEQUAL,
	NODE_INDEXER,
	NODE_INDEX_BLOCK,
	NODE_INDEX,
	NODE_INITIALIZER,
	NODE_DIMENSIONBLOCK,
	NODE_DIMENSION,
	NODE_MODULO,
	NODE_IF
};


static std::string nodeStringType[] = {
	"NODE_COMPILATION_UNIT",
	"NODE_EXPRESSION",
	"NODE_IDENTIFIER",
	"NODE_OP_CONJUNCTION",
	"NODE_OP_DISJUNCTION",
	"NODE_DECL",
	"NODE_DIGIT",
	"NODE_GLOBAL",
	"NODE_FUNCTION",
	"NODE_FUNCTIONHEADER",
	"NODE_VOID",
	"NODE_RETURNTYPE",
	"NODE_INT",
	"NODE_PARAMLIST",
	"NODE_PARAM",
	"NODE_BLOCK",
	"NODE_STATEMENT",
	"NODE_FACTOR",
	"NODE_DECLBLOCK",
	"NODE_OP_ASSIGN",
	"NODE_FUNCTIONDECL",
	"NODE_UNARY_ADD",
	"NODE_UNARY_SUBSTRACT",
	"NODE_BINARY_ADD",
	"NODE_BINARY_SUBSTRACT",
	"NODE_FUNCCALL",
	"NODE_FUNCARGS",
	"NODE_MULTIPLICATION",
	"NODE_DIVISION",
	"NODE_RETURN",
	"NODE_ASSEMBLY",
	"NODE_ASSEMBLY_LINE",
	"NODE_STRING",
	"NODE_REFERENCE",
	"NODE_CHAR",
	"NODE_EQUALITY",
	"NODE_WHILE",
	"NODE_INEQUALITY",
	"NODE_GREATER",
	"NODE_GREATEREQUAL",
	"NODE_LESS",
	"NODE_LESSEQUAL",
	"NODE_INDEXER",
	"NODE_INDEX_BLOCK",
	"NODE_INDEX",
	"NODE_INITIALIZER",
	"NODE_DIMENSIONBLOCK",
	"NODE_DIMENSION",
	"NODE_MODULO",
	"NODE_IF"
};


static NodeType getNodeFromToken(Token _token) {
	switch (_token._type)
	{
	case T_IDENTIFIER:			return NODE_IDENTIFIER; break;
	case T_DIGIT:				return NODE_DIGIT; break;
	case T_INT:					return NODE_INT; break;
	case T_CHAR:				return NODE_CHAR; break;
	case T_VOID:				return NODE_VOID; break;
	case T_OP_ASSIGN:			return NODE_OP_ASSIGN; break;
	case T_OP_BINARY_ADD:		return NODE_BINARY_ADD; break;
	case T_OP_BINARY_SUBSTRACT:	return NODE_BINARY_SUBSTRACT; break;
	case T_STAR:				return NODE_MULTIPLICATION; break;
	case T_OP_DIVIDE:			return NODE_DIVISION; break;
	case T_MOD:					return NODE_MODULO; break;
	case T_OP_EQUAL:			return NODE_EQUALITY; break;
	case T_OP_NOTEQUAL:			return NODE_INEQUALITY; break;
	case T_OP_GREATER:			return NODE_GREATER; break;
	case T_OP_GREATEREQUAL:		return NODE_GREATEREQUAL; break;
	case T_OP_LESS:				return NODE_LESS; break;
	case T_OP_LESSEQUAL:		return NODE_LESSEQUAL; break;
	case T_WHILE:				return NODE_WHILE; break;
	default:					break;
	}
}

class TreeNode 
{
public:
	TreeNode				*m_parent;
	std::vector<TreeNode*>	m_children;
	NodeType				m_nodeType;
	Token					m_token;

	TreeNode()
	{ 
	}

	TreeNode(NodeType type)
	{
		m_nodeType = type;
	}

	TreeNode(NodeType type, Token token)
	{
		m_nodeType = type;
		m_token = token;
	}

	void addChild(TreeNode* child)
	{
		if (child == nullptr)
			return;

		child->m_parent = this;
		m_children.push_back(child);
	}

	TreeNode* getChild(unsigned int index)
	{
		if (m_children.size() > index)
			return m_children._Myfirst()[index];

		return nullptr;
	}

	std::string getChildIdentifier(unsigned int index)
	{
		return getChild(index)->m_token._identifier;
	}

	void printNode(int _level) {

		std::cout << nodeStringType[m_nodeType] << " " << m_token.getStringValue() << std::endl;

		_level++;
		for (std::vector<TreeNode*>::iterator it = m_children.begin(); it != m_children.end(); ++it)
		{
			for (int i = 0; i < _level; ++i)
				std::cout << "    ";
			std::cout << "|---";

			(*it)->printNode(_level);
		}
	}
};

#endif