#ifndef MOVING_OBJ_ADAPTER
#define MOVING_OBJ_ADAPTER

#include "IoCcontainer.h"
#include "interfaces_obj/movingobject.h"
#include "command.h"

class MovingObjectAdapter: public IMovingObject
{
    IResolverContainer* _obj;
    public:
    MovingObjectAdapter( IResolverContainer* obj )
    {
        _obj = obj;
    }
  
    Vector2 getLocation()
    {
        return IoC::Resolve<Vector2, IResolverContainer*>("IMovingObject:Location.get", _obj);
    }

    void setLocation( Vector2 newValue )
    {
        IoC::Resolve<void, IResolverContainer* , Vector2>("IMovingObject:Location.set", _obj, newValue);
    }

    Vector2 getVelocity()
    {
        return IoC::Resolve<Vector2, IResolverContainer*>("IMovingObject:Velocity.get", _obj);
    }
};


class MOAdapterRegistration: public ICommand
{
    public:
    MOAdapterRegistration()
    {

    }

    void Execute()
    {
        IoC::Resolve<ICommand*, string, IResolverContainer*>("IoC.Register","Adapter.IMovingObject", new ResolverContainer<function<MovingObjectAdapter*(IResolverContainer*)>> (
            function<MovingObjectAdapter*(IResolverContainer*)>([&](IResolverContainer* obj){
                return new MovingObjectAdapter(obj);
            })
        ) )->Execute();
    }
};

#endif