#ifndef IOC_ADAPTER_TESTS
#define IOC_ADAPTER_TESTS

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../IoCcontainer.h"
#include "../command.h"

#include "../adapters/MovingObjectAdapter.h"
#include "../adapters/RotatingObjectAdapter.h"
#include "../AdapterCmd.h"


using ::testing::Return;
using ::testing::Throw;
using ::testing::InSequence;

#include <iostream>
#include <string>
#include <thread>
using namespace std;

/// @brief var adapter = IoC.Resolve("Adapter", typeof(IMovable), obj);
TEST(IoCAdapterTest, make_first_adapter)
{
    map<string, IResolverContainer*> *scope1= IoC::Resolve< map<string, IResolverContainer*>*,map<string, IResolverContainer*>*>( "IoC.Scope.New", nullptr );

    IoC::Resolve<void, map<string, IResolverContainer*>*>( "IoC.Scope.Current.Set", scope1 );

    SetAdaptersCmd cmd;
    cmd.Execute();

    string typeInterfaceName = _getType<IMovingObject*>(new IMovingObject*());

    AdapterRegister<MovingObjectAdapter> registerCmd(typeInterfaceName);
    registerCmd.Execute();

    map<string, IResolverContainer*> *obj= IoC::Resolve< map<string, IResolverContainer*>*,map<string, IResolverContainer*>*>( "IoC.Scope.New", nullptr );

    IResolverContainer* adapterResolver = IoC::Resolve<IResolverContainer*, string, IResolverContainer*>("Adapter", typeInterfaceName, new ResolverContainer< map<string, IResolverContainer*> *>(obj));
   
    //cout<<"adapter: "<<getType(adapterResolver)<<endl;  

    EXPECT_EQ( getType(adapterResolver),  "ResolverContainer<MovingObjectAdapter*>" );


    IoC::Resolve<void>( "IoC.Scope.Current.Clear" );
}

/// @brief var adapter = IoC.Resolve("Adapter.IMovingObject", obj);
TEST(IoCAdapterTest, make_second_adapter)
{
    map<string, IResolverContainer*> *scope1= IoC::Resolve< map<string, IResolverContainer*>*,map<string, IResolverContainer*>*>( "IoC.Scope.New", nullptr );
    
    IoC::Resolve<void, map<string, IResolverContainer*>*>( "IoC.Scope.Current.Set", scope1 );

    MovingObjectAdapterRegistration cmd;
    cmd.Execute();

    map<string, IResolverContainer*> *obj= IoC::Resolve< map<string, IResolverContainer*>*,map<string, IResolverContainer*>*>( "IoC.Scope.New", nullptr );
    MovingObjectAdapter* padapter = IoC::Resolve<MovingObjectAdapter*, IResolverContainer*>("Adapter.IMovingObject", new ResolverContainer< map<string, IResolverContainer*> *>(obj));

    EXPECT_EQ("MovingObjectAdapter*", _getType<MovingObjectAdapter*>(&padapter) );
  
    IoC::Resolve<void>( "IoC.Scope.Current.Clear" );
}

/// @brief реализация стратегий
TEST(IoCAdapterTest, make_third_adapter)
{
    map<string, IResolverContainer*> *scope1= IoC::Resolve< map<string, IResolverContainer*>*,map<string, IResolverContainer*>*>( "IoC.Scope.New", nullptr );
    IoC::Resolve<void, map<string, IResolverContainer*>*>( "IoC.Scope.Current.Set", scope1 );
    RotatingObjectAdapterRegistration cmd;
    cmd.Execute();

    map<string, IResolverContainer*> *obj= IoC::Resolve< map<string, IResolverContainer*>*,map<string, IResolverContainer*>*>( "IoC.Scope.New", nullptr );
    IoC::Resolve<void, map<string, IResolverContainer*>*>( "IoC.Scope.Current.Set", obj );
    
  //  IoC::Resolve<ICommand*, string, IResolverContainer*>("IoC.Register","Location", 
  //                          new ResolverContainer<function<Vector2()>> ( function<Vector2()>([&](){ return Vector2(1,1); }) ) )->Execute(); 
  //  IoC::Resolve<ICommand*, string, IResolverContainer*>("IoC.Register","Velocity", 
  //                              new ResolverContainer<function<Vector2()>> ( function<Vector2()>([&](){ return Vector2(1,1); }) ) )->Execute(); 
    IoC::Resolve<ICommand*, string, IResolverContainer*>("IoC.Register","Angle", 
                            new ResolverContainer<function<Angle()>> ( function<Angle()>([&](){ return Angle(1,4); }) ) )->Execute(); 
    
    IoC::Resolve<void, map<string, IResolverContainer*>*>( "IoC.Scope.Current.Set", scope1 );

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
    IoC::Resolve<ICommand*, string, IResolverContainer*>("IoC.Register","RotatingObject.Angle.get", 
                        new ResolverContainer<function<Angle(IResolverContainer*)>> 
                            ( function<Angle(IResolverContainer*)>
                            ([&](IResolverContainer* pObj)
                            { 
                                ResolverContainer<map<string, IResolverContainer*>*>* pContainer = dynamic_cast<ResolverContainer<map<string, IResolverContainer*>*>*>(pObj);
                                map<string, IResolverContainer*> *pMapObj = pContainer->get();
                                if ( pMapObj == nullptr )
                                    throw bad_cast();
                                IoC::Resolve<void, map<string, IResolverContainer*>*>( "IoC.Scope.Current.Set", pMapObj );
                                return IoC::Resolve<Angle>("Angle");
                            }) 
                        ) )->Execute(); 
    /*            
                                    
    IoC::Resolve<ICommand*, string, IResolverContainer*>("IoC.Register","RotatingObject.Angle.set", 
                                new ResolverContainer<function<void(IResolverContainer*, Angle)>> 
                                    ( function<void(IResolverContainer*,Angle)>
                                    ([&](IResolverContainer* pObj, Angle newValue)
                                        { 
                                            ResolverContainer<map<string, IResolverContainer*>*>* pContainer = dynamic_cast<ResolverContainer<map<string, IResolverContainer*>*>*>(pObj);
                                            map<string, IResolverContainer*> *pMapObj = pContainer->get();
                                            if ( pMapObj == nullptr )
                                                throw bad_cast();
                                            IoC::Resolve<void, map<string, IResolverContainer*>*>( "IoC.Scope.Current.Set", pMapObj );
                                            IoC::Resolve<ICommand*, string, IResolverContainer*>("IoC.Register","Angle", 
                                                new ResolverContainer<function<Angle()>> ( function<Angle()>([&](){ return Angle(1,4); }) ) )->Execute(); 
                                        }) 
                                    ) )->Execute();*/
    
    RotatingObjectAdapter* padapter = IoC::Resolve<RotatingObjectAdapter*, IResolverContainer*>("Adapter.IRotatingObject", new ResolverContainer< map<string, IResolverContainer*> *>(obj));
    // вызвать функции
    EXPECT_EQ("RotatingObjectAdapter*", _getType<RotatingObjectAdapter*>(&padapter) );

    EXPECT_FLOAT_EQ(padapter->getAngle().getRadAngle(), M_PI/2 );

    IoC::Resolve<void>( "IoC.Scope.Current.Clear" );
}

/// @brief реализаци функции не геттер и не сеттер не возвзвращающей ничего
TEST(IoCAdapterTest, make_new_function)
{
    map<string, IResolverContainer*> *scope1= IoC::Resolve< map<string, IResolverContainer*>*,map<string, IResolverContainer*>*>( "IoC.Scope.New", nullptr );

    IoC::Resolve<void, map<string, IResolverContainer*>*>( "IoC.Scope.Current.Set", scope1 );

    MovingObjectAdapterRegistration cmd;
    cmd.Execute();

    map<string, IResolverContainer*> *obj= IoC::Resolve< map<string, IResolverContainer*>*,map<string, IResolverContainer*>*>( "IoC.Scope.New", nullptr );
    // зарегистрировать зависимости

    IMovingObject* padapter = IoC::Resolve<MovingObjectAdapter*, IResolverContainer*>("Adapter.IMovingObject", new ResolverContainer< map<string, IResolverContainer*> *>(obj));
    // вызвать функции

    IoC::Resolve<void>( "IoC.Scope.Current.Clear" );
}

#endif
