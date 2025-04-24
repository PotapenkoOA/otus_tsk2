#ifndef ADAPTER_CMD
#define ADAPTER_CMD

#include "IoCcontainer.h"
#include "command.h"

#include <map>
using namespace std;


class SetAdaptersCmd: public ICommand
{ 
    public:
    SetAdaptersCmd(  )
    {
    }

    void Execute()
    {
       
           IoC::Resolve<ICommand*, string,  IResolverContainer*>( "IoC.Register", "Adapter", new ResolverContainer< function<IResolverContainer*(string, IResolverContainer*)>> (
            function<IResolverContainer*(string, IResolverContainer*)>([&](string typeName, IResolverContainer* obj){
               IResolverContainer* resolver = IoC::Resolve<IResolverContainer*, IResolverContainer*>(typeName, obj);

               return resolver;
            })
        ) )->Execute();
    }
};



template<typename T>
class AdapterRegister:ICommand
{   
    string _interfaceName;
    public:
    AdapterRegister(  string interfaceName )
    {
        _interfaceName = interfaceName;
    }
    
    void Execute()
    {
        IoC::Resolve<ICommand*, string,  IResolverContainer*>( "IoC.Register", _interfaceName, new ResolverContainer< function<IResolverContainer*(IResolverContainer*)>> (
            function<IResolverContainer*(IResolverContainer*)>([&](IResolverContainer* obj){
                return new ResolverContainer<T*>(new T(obj));
            })
        ) )->Execute();

        
       
    }
};

#endif