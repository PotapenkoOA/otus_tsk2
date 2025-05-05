#ifndef __THREADCMD_TEST__
#define __THREADCMD_TEST__

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../IoCcontainer.h"
#include "../EndPoints.h"

using ::testing::Return;
using ::testing::Throw;
using ::testing::InSequence;

#include <iostream>
#include <string>
#include <thread>
#include <map>

using namespace std;

#include "../json-develop/single_include/nlohmann/json.hpp"

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

/// @brief проверка разбора сообщения
TEST(InterpreterCmdTest, parse_msg )
{
    IoC::Resolve<ICommandPtr, string, IResolverContainer*>("IoC.Register", "Object.move", 
        new ResolverContainer< function<ICommandPtr(IObjectPtr)>> (
        function<ICommandPtr(IObjectPtr)>([](IObjectPtr obj){
           cout<<"lets move!\n";
           return make_shared<MOCK_CMD>();
        })
    ))->Execute();

    IoC::Resolve<ICommandPtr, string, IResolverContainer*>("IoC.Register", "Object.setLocation", 
        new ResolverContainer< function<ICommandPtr(IObjectPtr,Vector2)>> (
            function<ICommandPtr(IObjectPtr,Vector2)>([](IObjectPtr obj,Vector2 newValue){
                cout<<"set location!\n";
                return make_shared<MOCK_CMD>();
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
    
    SUCCEED();
}

/// @brief проверка постановки команды, заданной текстом в очередь игры
TEST(InterpreterCmdTest, add_interpreter_cmd )
{   
    shared_ptr<MOCK_CMD> pcmd1 = make_shared<MOCK_CMD>();
    IoC::Resolve<ICommandPtr, string, IResolverContainer*>("IoC.Register", "Object.move", 
        new ResolverContainer< function<ICommandPtr(IObjectPtr)>> (
        function<ICommandPtr(IObjectPtr)>([&](IObjectPtr obj){
           cout<<"lets move!\n";
           return pcmd1;
        })
    ))->Execute();

    IoC::Resolve<ICommandPtr, string, IResolverContainer*>("IoC.Register", "Object.setLocation", 
        new ResolverContainer< function<ICommandPtr(IObjectPtr,Vector2)>> (
            function<ICommandPtr(IObjectPtr,Vector2)>([&](IObjectPtr obj,Vector2 newValue){
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
   

/// @brief проверка результата команд на разных объектаx
TEST(InterpreterCmdTest, one_cmd_two_objects )
{
    shared_ptr<MOCK_CMD> pcmd1 = make_shared<MOCK_CMD>();
    IoC::Resolve<ICommandPtr, string, IResolverContainer*>("IoC.Register", "Object.move", 
        new ResolverContainer< function<ICommandPtr(IObjectPtr)>> (
        function<ICommandPtr(IObjectPtr)>([&](IObjectPtr obj){
           cout<<"lets move!\n";
           return pcmd1;
        })
    ))->Execute();

    IoC::Resolve<ICommandPtr, string, IResolverContainer*>("IoC.Register", "Object.setLocation", 
        new ResolverContainer< function<ICommandPtr(IObjectPtr,Vector2)>> (
            function<ICommandPtr(IObjectPtr,Vector2)>([&](IObjectPtr obj,Vector2 newValue){
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


/// @brief проверка результата команд на разных играх
TEST(InterpreterCmdTest, one_cmd_two_game )
{
    shared_ptr<MOCK_CMD> pcmd1 = make_shared<MOCK_CMD>();
    IoC::Resolve<ICommandPtr, string, IResolverContainer*>("IoC.Register", "Object.move", 
        new ResolverContainer< function<ICommandPtr(IObjectPtr)>> (
        function<ICommandPtr(IObjectPtr)>([&](IObjectPtr obj){
           cout<<"lets move!\n";
           return pcmd1;
        })
    ))->Execute();

    IoC::Resolve<ICommandPtr, string, IResolverContainer*>("IoC.Register", "Object.setLocation", 
        new ResolverContainer< function<ICommandPtr(IObjectPtr,Vector2)>> (
            function<ICommandPtr(IObjectPtr,Vector2)>([&](IObjectPtr obj,Vector2 newValue){
                cout<<"set location!\n";
                return pcmd1;
        })
    ))->Execute();

    IGamePtr pgame1 = make_shared<AnyGame>();
    IGamePtr pgame2 = make_shared<AnyGame>();
    map<string, IGamePtr> mapGames;
    mapGames["1"] = pgame1;
    mapGames["2"] = pgame2;

    Endpoint ep(&mapGames );

    IObjectPtr ship = IoC::Resolve<IObjectPtr, IObjectPtr> ("IoC.Scope.New", nullptr );
    pgame1->AddShip( "cowboy_bibop", ship );
    IObjectPtr ship2 = IoC::Resolve<IObjectPtr, IObjectPtr> ("IoC.Scope.New", nullptr );
    pgame2->AddShip( "fyrefly", ship2 );
    
    string Message = R"({"gameId":"1","objectId":"cowboy_bibop","cmdId":"setLocation", "args":[2,0]})"; 
    ep.MakeCommand(Message);

    Message = R"({"gameId":"2","objectId":"fyrefly","cmdId":"move"})"; 
    ep.MakeCommand(Message);
    
    EXPECT_CALL( *pcmd1, Execute() ).Times( 2 );   
    
    EXPECT_NO_THROW( pgame1->Start() );
    EXPECT_NO_THROW( pgame2->Start() );

    pgame1->Stop();  
    pgame2->Stop(); 

    SUCCEED();
}



#endif