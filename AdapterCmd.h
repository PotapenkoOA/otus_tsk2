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

 //  IoC::Resolve<ICommand*, string, IResolverContainer*>("IoC.Register","Location", 
  //                          new ResolverContainer<function<Vector2()>> ( function<Vector2()>([&](){ return Vector2(1,1); }) ) )->Execute(); 
  //  IoC::Resolve<ICommand*, string, IResolverContainer*>("IoC.Register","Velocity", 
  //                              new ResolverContainer<function<Vector2()>> ( function<Vector2()>([&](){ return Vector2(1,1); }) ) )->Execute(); 
   //IoC::Resolve<Vector2,IResolverContainer* >("MovingObject.Location.get", m_pObj);
 /*   IoC::Resolve<ICommand*, string, IResolverContainer*>("IoC.Register","MovingObject.Location.get", 
        new ResolverContainer<function<Vector2(IResolverContainer*)>> 
            ( function<Vector2(IResolverContainer*)>
            ([&](IResolverContainer* pObj)
            { 
                ResolverContainer<map<string, IResolverContainer*>*>* pContainer = dynamic_cast<ResolverContainer<map<string, IResolverContainer*>*>*>(pObj);
                map<string, IResolverContainer*> *pMapObj = pContainer->get();
                if ( pMapObj == nullptr )
                    throw bad_cast();
                IoC::Resolve<void, map<string, IResolverContainer*>*>( "IoC.Scope.Current.Set", pMapObj );
                return IoC::Resolve<Vector2>("Location"); 
            }) 
        ) )->Execute(); 

    IoC::Resolve<ICommand*, string, IResolverContainer*>("IoC.Register","MovingObject.Velocity.get", 
        new ResolverContainer<function<Vector2(IResolverContainer*)>> 
            ( function<Vector2(IResolverContainer*)>
            ([&](IResolverContainer* pObj)
                { 
                    ResolverContainer<map<string, IResolverContainer*>*>* pContainer = dynamic_cast<ResolverContainer<map<string, IResolverContainer*>*>*>(pObj);
                    map<string, IResolverContainer*> *pMapObj = pContainer->get();
                    if ( pMapObj == nullptr )
                        throw bad_cast();
                    IoC::Resolve<void, map<string, IResolverContainer*>*>( "IoC.Scope.Current.Set", pMapObj );
                    return IoC::Resolve<Vector2>("Velocity"); 
                }) 
            ) )->Execute();

    IoC::Resolve<ICommand*, string, IResolverContainer*>("IoC.Register","MovingObject.Location.set", 
                new ResolverContainer<function<void(IResolverContainer*, Vector2)>> 
                    ( function<void(IResolverContainer*,Vector2)>
                    ([&](IResolverContainer* pObj, Vector2 newValue)
                        { 
                            ResolverContainer<map<string, IResolverContainer*>*>* pContainer = dynamic_cast<ResolverContainer<map<string, IResolverContainer*>*>*>(pObj);
                            map<string, IResolverContainer*> *pMapObj = pContainer->get();
                            if ( pMapObj == nullptr )
                                throw bad_cast();
                            IoC::Resolve<void, map<string, IResolverContainer*>*>( "IoC.Scope.Current.Set", pMapObj );
                            IoC::Resolve<ICommand*, string, IResolverContainer*>("IoC.Register","Location", 
                                new ResolverContainer<function<Vector2()>> ( function<Vector2()>([&](){ return newValue; }) ) )->Execute(); 
                        }) 
                    ) )->Execute();
                    */
#endif