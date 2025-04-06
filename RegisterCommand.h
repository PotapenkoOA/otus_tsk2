#ifndef __REGISTERCMD__
#define __REGISTERCMD__

#include "command.h"
#include "IoCcontainer.h"
#include "IResolverContainer.h"

class RegisterCommand: public ICommand
{
    string _dependency;
    IResolverContainer *_pcontainer;

    map<string, IResolverContainer*> *_currentScope;

public:
    RegisterCommand( void* currentScope, string dependency, IResolverContainer* pcontainer )
    {
        _currentScope = (map<string, IResolverContainer*> *)currentScope;
        _dependency = dependency;
        _pcontainer = pcontainer;       
    }

    void Execute()
    {
        if(_currentScope == nullptr)
            throw new invalid_argument("RegisterCommand: scope is nullptr");
       (*_currentScope)[_dependency] = _pcontainer;
    }
};

#endif