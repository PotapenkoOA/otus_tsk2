#ifndef __DEPENDENCYRESOLVER__
#define __DEPENDENCYRESOLVER__

#include "IResolverContainer.h"
#include "RegisterCommand.h"

#include <map>
#include <thread>

using namespace std;


class IDependencyResolver
{
protected:
    /* data */
public:
    virtual  ~IDependencyResolver() = default;

    virtual IResolverContainer* Resolve(string dependency) = 0;
};

class DependencyResolver: public IDependencyResolver
{
    thread_local static IObjectPtr _pCurrentScope;

    IObjectPtr _pRootScope;

    public:
    DependencyResolver()
    {
        _pCurrentScope = nullptr;
        _pRootScope = make_shared<map< string, IResolverContainer*>>();

        // _dependencies["IoC.Scope.Current.Set"] - получает скоуп и делает его текущим
        map< string, IResolverContainer*>* pRootScope = _pRootScope.get();
        (*pRootScope)["IoC.Scope.Current.Set"] = new ResolverContainer<function< void(IObjectPtr)> >(
            function< void(IObjectPtr)> (
                [&](IObjectPtr current)
                {
                    _pCurrentScope = current;
                }
            )
        );

        // _dependencies["IoC.Scope.Current.Clear"] - очищает текущий скоуп
        (*pRootScope)["IoC.Scope.Current.Clear"] = new ResolverContainer<function< void(void)>>(
            function< void(void)> (
                [&](void)
                {
                    _pCurrentScope = nullptr;
                }
            )
        );

        // _dependencies["IoC.Scope.Current"] - возвращает текущий скоуп
        (*pRootScope)["IoC.Scope.Current"] = new ResolverContainer<function< IObjectPtr(void)>>(
            function< IObjectPtr(void)> (
                [&](void)
                {
                    return  (_pCurrentScope == nullptr) ? _pRootScope : _pCurrentScope;
                }
            )
        );

        
        //  _dependencies["IoC.Scope.Parent"] = exception для рутового скоупа
        (*pRootScope)["IoC.Scope.Parent"] = new ResolverContainer< function< IObjectPtr(void)>>(
            function< IObjectPtr(void)>([]()
            {
                throw exception();
                return nullptr;
            })
        );
           
        //  _dependencies["IoC.Scope.Create.Empty"] = создание пустого скоупа
        (*_pRootScope)["IoC.Scope.New.Empty"] = new ResolverContainer<function< IObjectPtr(void)>>(
            function< IObjectPtr(void)> ( []() { return  make_shared<map< string, IResolverContainer*>>();})
        );

        //  _dependencies["IoC.Scope.Create"] - создание скоупа с перентом, если указан
        (*_pRootScope)["IoC.Scope.New"] = new ResolverContainer<function< IObjectPtr(IObjectPtr)>>(
            function< IObjectPtr(IObjectPtr)> (
                [&](IObjectPtr parent)
                {
                    IObjectPtr pCreatingScope = 
                            ((ResolverContainer<function< IObjectPtr(void)>>*)(*_pRootScope)["IoC.Scope.New.Empty"])->get()();
                    
                    //map<string, IResolverContainer*>* parent
                    if( parent == nullptr )
                    {
                        ResolverContainer<function< IObjectPtr(void)>> *pContainer =
                        (ResolverContainer<function< IObjectPtr(void)>> *) (*_pRootScope)["IoC.Scope.Current"];
            
                        parent = pContainer->get()(); 
                        (*pCreatingScope)["IoC.Scope.Parent"] = new ResolverContainer<function<IObjectPtr(void)>>(
                            function<IObjectPtr(void)>([parent]()
                            {      
                                return parent;
                            })
                        );
                    }
                    else
                    {
                        (*pCreatingScope)["IoC.Scope.Parent"] = new ResolverContainer<function<IObjectPtr(void)>>(
                            function<IObjectPtr(void)>([parent]()
                            { 
                                return parent;
                            })
                        );
                    }
                    return  pCreatingScope;
                }
            )
        );

        // инициализация базовых потребностей
        (*_pRootScope)["IoC.Register"] =  new ResolverContainer<function<ICommandPtr(string, IResolverContainer*)>>( 
            function< ICommandPtr ( string, IResolverContainer* )>(
                [&](string dependency, IResolverContainer* pResolver)
                {
                    return make_shared<RegisterCommand> ((_pCurrentScope != nullptr)? _pCurrentScope : _pRootScope, 
                        dependency, pResolver );
                }
             )
        );  
    }

    IResolverContainer* Resolve( string dependency )
    {
        ResolverContainer<function< IObjectPtr(void)>> *pContainer =
            (ResolverContainer<function< IObjectPtr(void)>> *) (*_pRootScope)["IoC.Scope.Current"];
        return Resolve(pContainer->get()(), dependency);
    }

    IResolverContainer* Resolve( IObjectPtr dependencies, string dependency )
    {
        IObjectPtr _dependencies = dependencies;
        while( 1 )
        {
            if( _dependencies->count(dependency) != 0 )
            {
                //cout<<_dependencies<<" find dependency:"<<" "<<dependency<<endl;
                return (*_dependencies)[dependency];
            }
            else  
            {
                /// обратиться к родительскому скоупу
                ResolverContainer<function<IObjectPtr(void)>>* pContainer =
                        (ResolverContainer <function<IObjectPtr(void)>>*)(*_dependencies)[ "IoC.Scope.Parent" ];
                
                _dependencies = pContainer->get()();
               
                return Resolve( _dependencies,dependency);
            }
        }

        return nullptr;
    }
};

thread_local IObjectPtr DependencyResolver::_pCurrentScope = nullptr;

#endif