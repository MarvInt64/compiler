#ifndef SCOPE_H_
#define SCOPE_H_

#include <vector>
#include "Symtable.h"

class Scope
{
public:
	Scope()
	{
		symbolTable = new Symtable();
	}

	void addSymbol(Symbol* symbol)
	{
		symbolTable->addSymbol(symbol);
	}

	Scope* createScope()
	{
		Scope* scope = new Scope();
		scope->parentScope = this;
		scopeList.push_back(scope);

		return scope;
	}

	Scope* leaveScope()
	{
		return parentScope;
	}

	std::vector<Scope*> scopeList;
	Scope* parentScope;
	Symtable* symbolTable;
};

#endif 