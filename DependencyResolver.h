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
    thread_local static map<string, IResolverContainer*>* _pCurrentScope;

    map<string, IResolverContainer*> _rootScope;

    public:
    DependencyResolver()
    {
        _pCurrentScope = nullptr;

        // _dependencies["IoC.Scope.Current.Set"] - получает скоуп и делает его текущим
        _rootScope["IoC.Scope.Current.Set"] = new ResolverContainer<function< void(map<string, IResolverContainer*>*)>>(
            function< void(map<string, IResolverContainer*>*)> (
                [&](map<string, IResolverContainer*>* current)
                {
                    _pCurrentScope = current;
                }
            )
        );

        // _dependencies["IoC.Scope.Current.Clear"] - очищает текущий скоуп
        _rootScope["IoC.Scope.Current.Clear"] = new ResolverContainer<function< void(void)>>(
            function< void(void)> (
                [&](void)
                {
                    _pCurrentScope = nullptr;
                }
            )
        );

        // _dependencies["IoC.Scope.Current"] - возвращает текущий скоуп
        _rootScope["IoC.Scope.Current"] = new ResolverContainer<function< map<string, IResolverContainer*>*(void)>>(
            function< map<string, IResolverContainer*>*(void)> (
                [&](void)
                {
                    return  (_pCurrentScope == nullptr) ? &_rootScope : _pCurrentScope;
                }
            )
        );

        
        //  _dependencies["IoC.Scope.Parent"] = exception для рутового скоупа
        _rootScope["IoC.Scope.Parent"] = new ResolverContainer<function<map<string, IResolverContainer*>*(void)>>(
            function<map<string, IResolverContainer*>*(void)>([]()
            {
                throw exception();
                return nullptr;
            })
        );
           
        //  _dependencies["IoC.Scope.Create.Empty"] = создание пустого скоупа
        _rootScope["IoC.Scope.New.Empty"] = new ResolverContainer<function< map<string, IResolverContainer*>*(void)>>(
            function< map<string, IResolverContainer*>*(void)> ( []() { return  new map<string, IResolverContainer*>();})
        );

        //  _dependencies["IoC.Scope.Create"] - создание скоупа с перентом, если указан
        _rootScope["IoC.Scope.New"] = new ResolverContainer<function< map<string, IResolverContainer*>*(map<string, IResolverContainer*>*)>>(
            function< map<string, IResolverContainer*>*(map<string, IResolverContainer*>*)> (
                [&](map<string, IResolverContainer*>* parent)
                {
                    map<string, IResolverContainer*> *pCreatingScope = 
                            ((ResolverContainer<function< map<string, IResolverContainer*>*(void)>>*)_rootScope["IoC.Scope.New.Empty"])->get()();
                    
                    //map<string, IResolverContainer*>* parent
                    if( parent == nullptr )
                    {
                        ResolverContainer<function< map<string, IResolverContainer*>*(void)>> *pContainer =
                        (ResolverContainer<function< map<string, IResolverContainer*>*(void)>> *) _rootScope["IoC.Scope.Current"];
            
                        parent = pContainer->get()(); 
                        (*pCreatingScope)["IoC.Scope.Parent"] = new ResolverContainer<function<map<string, IResolverContainer*>*(void)>>(
                            function<map<string, IResolverContainer*>*(void)>([parent]()
                            {      
                                return parent;
                            })
                        );
                    }
                    else
                    {
                        (*pCreatingScope)["IoC.Scope.Parent"] = new ResolverContainer<function<map<string, IResolverContainer*>*(void)>>(
                            function<map<string, IResolverContainer*>*(void)>([parent]()
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
        _rootScope["IoC.Register"] =  new ResolverContainer<function<ICommand*(string, IResolverContainer*)>>( 
            function<ICommand*(string, IResolverContainer*)>(
                [&](string dependency, IResolverContainer* pResolver)
                {
                    return new RegisterCommand(
                        (_pCurrentScope != nullptr)? _pCurrentScope : &_rootScope, dependency, pResolver
                        );
                }
             )
        );  
    }

    IResolverContainer* Resolve( string dependency )
    {
        ResolverContainer<function< map<string, IResolverContainer*>*(void)>> *pContainer =
            (ResolverContainer<function< map<string, IResolverContainer*>*(void)>> *) _rootScope["IoC.Scope.Current"];
        return Resolve(pContainer->get()(), dependency);
    }

    IResolverContainer* Resolve( map<string, IResolverContainer*> *dependencies, string dependency )
    {
        map<string, IResolverContainer*> *_dependencies = dependencies;
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
                ResolverContainer<function<map<string, IResolverContainer*>*(void)>>* pContainer =
                        (ResolverContainer <function<map<string, IResolverContainer*>*(void)>>*)(*_dependencies)[ "IoC.Scope.Parent" ];
                
                _dependencies = pContainer->get()();
               
                return Resolve( _dependencies,dependency);
            }
        }

        return nullptr;
    }
};

thread_local map<string, IResolverContainer*>* DependencyResolver::_pCurrentScope = nullptr;

#endif