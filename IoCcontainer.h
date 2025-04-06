#ifndef __IOCCONTAINER__
#define __IOCCONTAINER__

#include <string>
using namespace std;

#include "IResolverContainer.h"
#include "DependencyResolver.h"

class IoC
{     
    static IDependencyResolver* resolver;

public: 
 
    template<typename T, typename ...Args >
    static T Resolve( string dependency, Args... args )
    {        
        ResolverContainer<function<T(Args...)>>* pContainer = 
                        dynamic_cast<ResolverContainer<function<T(Args...)>>*>(IoC::resolver->Resolve(dependency));
        
      // cout<<"Resolve:"<< getType(IoC::resolver->Resolve(dependency))<<endl<<endl;  
        if(pContainer)
            return  pContainer->get()(args...);
        else throw std::bad_cast();  
    }
};

IDependencyResolver* IoC::resolver = new DependencyResolver();

#endif