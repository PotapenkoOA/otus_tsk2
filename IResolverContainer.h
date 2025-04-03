
#ifndef __IRESOLVECONTAINER__
#define __IRESOLVECONTAINER__

#include <map>
#include <string>
using namespace std;

class IResolverContainer
{
    public:
        virtual ~IResolverContainer() = default;
};

template<typename Type >
class ResolverContainer: public IResolverContainer
{
    Type m_Resolver;

public:    
    ResolverContainer(Type resolver)
    {
        m_Resolver = resolver;
    }    

    Type get()
    {
        return m_Resolver;
    }
};

#endif