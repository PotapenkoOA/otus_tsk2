#ifndef __JWTVERIFY_TEST__
#define __JWTVERIFY_TEST__

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../IoCcontainer.h"
#include "../EndPoints.h"
//#include "Endpoint_test.h"

#include "../EPsrv/jwt_library.h"

using ::testing::Return;
using ::testing::Throw;
using ::testing::InSequence;

#include <iostream>
#include <string>
#include <thread>
#include <map>

using namespace std;

#include <boost/json.hpp>

/*
    Message Format:
    {
        "gameId":"nameGame",
        "objectId":"nameObj",
        "cmdId":"nameCmd", 
        "args":[2,0]
    }
*/
class MOCK_CMD:public ICommand{
    public:
    //virtual void Execute() = 0;
    MOCK_METHOD(void, Execute, (), (override));    
};

/// @brief успешная проверка 
TEST(JWTVerify, good_jwt_msg )
{
    IoC::Resolve<ICommandPtr, string, IResolverContainerPtr>("IoC.Register", "Object.move", 
        make_container (
        function<ICommandPtr(IObjectPtr)>([](IObjectPtr obj){
           cout<<"lets move!\n";
           return make_shared<MOCK_CMD>();
        })
    ))->Execute();

    Endpoint ep;

    string Message = ep.ReceiveMessage();
   
    EXPECT_TRUE( ep.MakeCommand(Message));

    SUCCEED();
    
}
/*
/// @brief провальная проверка
TEST(JWTVerify, fail_jwt_msg )
{   
    shared_ptr<MOCK_CMD> pcmd1 = make_shared<MOCK_CMD>();
    IoC::Resolve<ICommandPtr, string, IResolverContainer*>("IoC.Register", "Object.move", 
        new ResolverContainer< function<ICommandPtr(IObjectPtr)>> (
        function([&](IObjectPtr obj){
           cout<<"lets move!\n";
           return pcmd1;
        })
    ))->Execute();

    IoC::Resolve<ICommandPtr, string, IResolverContainer*>("IoC.Register", "Object.setLocation", 
        new ResolverContainer< function<ICommandPtr(IObjectPtr,Vector2)>> (
            function([&](IObjectPtr obj,Vector2 newValue){
                cout<<"set location!\n";
                return pcmd1;
        })
    ))->Execute();

    IGamePtr pgame = make_shared<AnyGame>();
    map<string, IGamePtr> mapGames;
    mapGames["123"] = pgame;

    IObjectPtr ship = IoC::Resolve<IObjectPtr, IObjectPtr> ("IoC.Scope.New", nullptr );
    pgame->AddShip( "cowboy_bibop", ship );
    
    Endpoint ep(&mapGames );
   
    string Message = R"({"gameId":"123","objectId":"cowboy_bibop","cmdId":"setLocation", "args":[2,0]})"; 
    ep.MakeCommand(Message);

    Message = R"({"gameId":"123","objectId":"cowboy_bibop","cmdId":"move"})"; 
    ep.MakeCommand(Message);
    
    EXPECT_CALL( *pcmd1, Execute() ).Times( 2 );   
    
    EXPECT_NO_THROW( pgame->Start() );

    pgame->Stop();

    SUCCEED();
}
   

/// @brief управление игровым объектом
TEST(JWTVerify, control_objects )
{
    shared_ptr<MOCK_CMD> pcmd1 = make_shared<MOCK_CMD>();
    IoC::Resolve<ICommandPtr, string, IResolverContainer*>("IoC.Register", "Object.move", 
        new ResolverContainer< function<ICommandPtr(IObjectPtr)>> (
        function([&](IObjectPtr obj){
           cout<<"lets move!\n";
           return pcmd1;
        })
    ))->Execute();

    IoC::Resolve<ICommandPtr, string, IResolverContainer*>("IoC.Register", "Object.setLocation", 
        new ResolverContainer< function<ICommandPtr(IObjectPtr,Vector2)>> (
            function([&](IObjectPtr obj,Vector2 newValue){
                cout<<"set location!\n";
                return pcmd1;
        })
    ))->Execute();

    IGamePtr pgame = make_shared<AnyGame>();
    map<string, IGamePtr> mapGames;
    mapGames["123"] = pgame;

    IObjectPtr ship1 = IoC::Resolve<IObjectPtr, IObjectPtr> ("IoC.Scope.New", nullptr );
    pgame->AddShip( "cowboy_bibop", ship1 );
    IObjectPtr ship2 = IoC::Resolve<IObjectPtr, IObjectPtr> ("IoC.Scope.New", nullptr );
    pgame->AddShip( "fyrefly", ship2 );
    
    Endpoint ep(&mapGames );
   
    string Message = R"({"gameId":"123","objectId":"cowboy_bibop","cmdId":"setLocation", "args":[2,0]})"; 
    ep.MakeCommand(Message);

    Message = R"({"gameId":"123","objectId":"fyrefly","cmdId":"move"})"; 
    ep.MakeCommand(Message);
    
    EXPECT_CALL( *pcmd1, Execute() ).Times( 2 );   
    
    EXPECT_NO_THROW( pgame->Start() );

    pgame->Stop();
   
    SUCCEED();
}

*/

#endif