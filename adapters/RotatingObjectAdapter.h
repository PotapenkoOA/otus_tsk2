#ifndef ROTATINGOBJECT_ADAPTER
#define ROTATINGOBJECT_ADAPTER

#include "../IoCcontainer.h"
#include "../interfaces_obj/rotatingobject.h"

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

class RotatingObjectAdapterRegistration: public ICommand
{
	public:
	RotatingObjectAdapterRegistration()
	{
	
	}
	
	void Execute()
	{
		IoC::Resolve<ICommand*, string, IResolverContainer*>("IoC.Register","Adapter.IRotatingObject", new ResolverContainer<function<RotatingObjectAdapter*(IResolverContainer*)>> (
			function<RotatingObjectAdapter*(IResolverContainer*)>([&](IResolverContainer* obj){
				return new RotatingObjectAdapter(obj);
			})
		) )->Execute();
	}
};

#endif
