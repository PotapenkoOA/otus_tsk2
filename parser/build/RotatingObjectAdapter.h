#ifndef MOVING_OBJ_ADAPTER
#define MOVING_OBJ_ADAPTER

#include "IoCcontainer.h"
#include "RotatingObject.h"

 class RotatingObjectAdapter: public IRotatingObject {

	IResolverContainer* m_pObj;

	public:
	RotatingObjectAdapter( IResolverContainer* pObj ) {
		m_pObj = pObj;
	}

	Angle getAngle(  ){
		return IoC::Resolve<Angle,IResolverContainer* >("RotatingObject.Angle.get", m_pObj);
	}

	Angle getAngularVelocity(  ){
		return IoC::Resolve<Angle,IResolverContainer* >("RotatingObject.AngularVelocity.get", m_pObj);
	}

	void setAngle( Angle a){
		IoC::Resolve<void,IResolverContainer* ,Angle >("RotatingObject.Angle.set", m_pObj ,a);
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
