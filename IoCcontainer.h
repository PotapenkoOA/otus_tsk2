#ifndef __IOCCONTAINER__
#define __IOCCONTAINER__

#include <iostream>
#include <map>
#include <list>
#include <string>
using namespace std;

#include <stdarg.h>
#include "IResolverContainer.h"
#include "RegisterCommand.h"

string _getType(IResolverContainer *c)
{
    int status;  
    const type_info& typeInfo = typeid(*c);
    char* demangled = abi::__cxa_demangle(typeInfo.name(), nullptr, nullptr, &status);
    return (status == 0) ? demangled : typeInfo.name();
}

class IoC
{   
    static map<string, IResolverContainer*> currentScope;
public: 
    
    static void Init()
    {
        currentScope["IoC.Register"] =  new ResolverContainer<function<ICommand*(string, IResolverContainer*)>>( 
            function<ICommand*(string, IResolverContainer*)>(
                [&](string dependency, IResolverContainer* pResolver)
                {
                    return new RegisterCommand(
                            &currentScope, dependency, pResolver
                        );
                }
             )
        );  
    }    

    template<typename T, typename ...Args >
    static T Resolve( string dependency, Args... args )
    {        
        ResolverContainer<function<T(Args...)>>* pContainer = dynamic_cast<ResolverContainer<function<T(Args...)>>*>(currentScope[dependency]);
        
        if(pContainer)
            return  pContainer->get()(args...);
        else throw std::bad_cast();  
    }
};

map<string, IResolverContainer*> IoC::currentScope;

#endif