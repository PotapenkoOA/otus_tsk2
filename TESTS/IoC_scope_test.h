#ifndef IOC_SCOPE_TESTS
#define IOC_SCOPE_TESTS

#include <gtest/gtest.h>
#include <gmock/gmock.h>

<<<<<<< HEAD:TESTS/IoC_scope_test.h
#include "../IoCcontainer.h"
#include "../command.h"
=======
#include "IoCcontainer.h"
#include "command.h"
>>>>>>> befe291f8ee9596abd9bdc96875a41b33c06eb88:IoC_scope_test.h

using ::testing::Return;
using ::testing::Throw;
using ::testing::InSequence;

#include <iostream>
#include <string>
#include <thread>
using namespace std;


TEST(IoCScopeTest, set_scope)
{
    map<string, IResolverContainer*> *scope1= IoC::Resolve< map<string, IResolverContainer*>*,map<string, IResolverContainer*>*>( "IoC.Scope.New", nullptr );

    IoC::Resolve<void, map<string, IResolverContainer*>*>( "IoC.Scope.Current.Set", scope1 );

    map<string, IResolverContainer*> *current= IoC::Resolve<map<string, IResolverContainer*>*>( "IoC.Scope.Current" );

    EXPECT_TRUE( scope1 == current );

    IoC::Resolve<void>( "IoC.Scope.Current.Clear" );
}

TEST(IoCScopeTest, set_child_scope)
{
    map<string, IResolverContainer*> *scope1= IoC::Resolve< map<string, IResolverContainer*>*,map<string, IResolverContainer*>*>( "IoC.Scope.New", nullptr );

    map<string, IResolverContainer*> *scope2= IoC::Resolve< map<string, IResolverContainer*>*,map<string, IResolverContainer*>*>( "IoC.Scope.New", scope1 );

    IoC::Resolve<void, map<string, IResolverContainer*>*>( "IoC.Scope.Current.Set", scope2 );

    map<string, IResolverContainer*> *parent= IoC::Resolve<map<string, IResolverContainer*>*>( "IoC.Scope.Parent" );

    EXPECT_TRUE( scope1 == parent );

    IoC::Resolve<void>( "IoC.Scope.Current.Clear" );
}


TEST(IoCScopeTest, register_dependency)
{
    map<string, IResolverContainer*> *scope1= IoC::Resolve< map<string, IResolverContainer*>*,map<string, IResolverContainer*>*>( "IoC.Scope.New", nullptr );
  
    IoC::Resolve<void, map<string, IResolverContainer*>*>( "IoC.Scope.Current.Set", scope1 );

    IoC::Resolve<ICommand*, string, IResolverContainer*>( "IoC.Register", "two", new ResolverContainer<function<int(void)>>( function<int(void)>([](){return 2;}) ) )->Execute();

    EXPECT_EQ(IoC::Resolve<int>("two"), 2);

    IoC::Resolve<void>( "IoC.Scope.Current.Clear" );
}


TEST(IoCScopeTest, register_dependency2)
{
    /// регистрация в разных скоупах
    map<string, IResolverContainer*> *scope1= IoC::Resolve< map<string, IResolverContainer*>*,map<string, IResolverContainer*>*>( "IoC.Scope.New", nullptr );
  
    IoC::Resolve<void, map<string, IResolverContainer*>*>( "IoC.Scope.Current.Set", scope1 );
   
    IoC::Resolve<ICommand*, string, IResolverContainer*>( "IoC.Register", "aaaa", new ResolverContainer<function<int(void)>>( function<int(void)>([](){return 2;}) ) )->Execute();

    map<string, IResolverContainer*> *parent0=  IoC::Resolve<map<string, IResolverContainer*>*>( "IoC.Scope.Parent" );
    
    map<string, IResolverContainer*> *scope2= IoC::Resolve< map<string, IResolverContainer*>*,map<string, IResolverContainer*>*>( "IoC.Scope.New", parent0 );
    
    IoC::Resolve<void, map<string, IResolverContainer*>*>( "IoC.Scope.Current.Set", scope2 );
  
    EXPECT_ANY_THROW(IoC::Resolve<int>("aaaa"));

    IoC::Resolve<void>( "IoC.Scope.Current.Clear" );
}


TEST(IoCScopeTest, register_dependency3)
{
    /// многопоточные тесты
    map<string, IResolverContainer*> *scope1= IoC::Resolve< map<string, IResolverContainer*>*,map<string, IResolverContainer*>*>( "IoC.Scope.New", nullptr );
  
    IoC::Resolve<void, map<string, IResolverContainer*>*>( "IoC.Scope.Current.Set", scope1 );
    IoC::Resolve<ICommand*, string, IResolverContainer*>( "IoC.Register", "aaaa", new ResolverContainer<function<int(void)>>( function<int(void)>([](){return 5;}) ) )->Execute();
    
    thread t(
        []()
        {
            map<string, IResolverContainer*> *scope2= IoC::Resolve< map<string, IResolverContainer*>*,map<string, IResolverContainer*>*>( "IoC.Scope.New", nullptr );
    
            IoC::Resolve<void, map<string, IResolverContainer*>*>( "IoC.Scope.Current.Set", scope2 );

            IoC::Resolve<ICommand*, string, IResolverContainer*>( "IoC.Register", "aaaa", new ResolverContainer<function<int(void)>>( function<int(void)>([](){return 7;}) ) )->Execute();
            
            EXPECT_EQ(IoC::Resolve<int>("aaaa"), 7);
        }
    );
    t.join();

    EXPECT_EQ(IoC::Resolve<int>("aaaa"), 5);

    IoC::Resolve<void>( "IoC.Scope.Current.Clear" );
}


#endif
