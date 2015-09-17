#ifndef SYMTAbLE_H_
#define SYMTABLE_H_

#include <string>
#include <vector>

enum SymbolType
{
	VARIABLE,
	FUNCTION
};

enum TypeSpecifier
{
	INT,
	DOUBLE,
	STRING,
	FLOAT,
	CHAR,
	VOID
};

struct Symbol
{
	std::string _symbolName;
	TypeSpecifier _typeSpecifier;
	SymbolType _symbolType;
	int _address;

	Symbol(const std::string& name)
	{
		_symbolName = name;
	}

	Symbol(const std::string& name, SymbolType symbolType, TypeSpecifier specifier)
	{
		_symbolName = name;
		_typeSpecifier = specifier;
		_symbolType = symbolType;
	}

	Symbol(const std::string& name, SymbolType symbolType, NodeType tokenType)
	{
		_symbolName = name;
		_typeSpecifier = toTypeSpecifier(tokenType);
		_symbolType = symbolType;
	}

	static TypeSpecifier toTypeSpecifier(NodeType type)
	{
		switch(type)
		{
		case NodeType::NODE_INT:		return TypeSpecifier::INT; break;
		case NodeType::NODE_STRING:		return TypeSpecifier::STRING; break;
		case NodeType::NODE_VOID:		return TypeSpecifier::VOID; break;
		}
	}
};

class Symtable
{
public:
	Symtable()
	{
		_symbolList = new std::vector<Symbol*>();
	}

	unsigned int getSize()
	{
		return _symbolList->size();
	}

	void addSymbol(Symbol* symbol)
	{
		if (!hasSymbolName(symbol->_symbolName))
		{
			symbol->_address = (_symbolList->size()+1)*4;
			_symbolList->push_back(symbol);
		}
		else
		{
			std::cout << "The symbol '" << symbol->_symbolName << "' is already declared in the current scope." << std::endl;
			delete symbol;
		}
	}

	Symbol* getSymbolbyName(const std::string& name)
	{
		for (Symbol* s : *_symbolList)
		{
			if (s->_symbolName == name)
				return s;
		}

		return nullptr;
	}

	bool hasSymbolName(const std::string& name)
	{
		for (Symbol* s : *_symbolList)
		{
			if (s->_symbolName == name)
				return true;
		}

		return false;
	}

private:
	std::vector<Symbol*>* _symbolList;
};

#endif