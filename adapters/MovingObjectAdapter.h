#ifndef MOVINGOBJECT_ADAPTER
#define MOVINGOBJECT_ADAPTER

#include "..\IoCcontainer.h"
#include "..\interfaces_obj\MovingObject.h"

 class MovingObjectAdapter: public IMovingObject {

	IResolverContainer* m_pObj;

	public:
	MovingObjectAdapter( IResolverContainer* pObj ) {
		m_pObj = pObj;
	}

	Vector2 getLocation(  ){
		return IoC::Resolve<Vector2,IResolverContainer* >("MovingObject.Location.get", m_pObj);
	}

	Vector2 getVelocity(  ){
		return IoC::Resolve<Vector2,IResolverContainer* >("MovingObject.Velocity.get", m_pObj);
	}

	void setLocation( Vector2 newValue ){
		IoC::Resolve<void,IResolverContainer* ,Vector2 >("MovingObject.Location.set", m_pObj ,newValue );
	}

};

class MovingObjectAdapterRegistration: public ICommand
{
	public:
	MovingObjectAdapterRegistration()
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
