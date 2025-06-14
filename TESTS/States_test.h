#ifndef __THREADCMD_TEST__
#define __THREADCMD_TEST__

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../IoCcontainer.h"
#include "../command.h"
#include "../CommandQueue.h"
#include "../ThreadCmd.h"
#include "../stateCnageCmd.h"

using ::testing::Return;
using ::testing::Throw;
using ::testing::InSequence;

#include <iostream>
#include <string>
#include <thread>

using namespace std;

class MOCK_CMD:public ICommand{
    public:
    //virtual void Execute() = 0;
    MOCK_METHOD(void, Execute, (), (override));    
};

/// @brief  проверить, что после команды _HardStopCmd поток останавливается
TEST(StateTest, hard_stop_cmd_work )
{
    CmdQueuePtr pQueue = make_shared<CmdQueue>();

    IoC::Resolve<  ICommandPtr, string, IResolverContainerPtr >("IoC.Register", "State", 
        make_container (
        function<IStatePtr()>([&](){
           return make_shared<OrdinaryState>(pQueue);
        })
    ))->Execute();

    shared_ptr<MOCK_CMD> pcmd = make_shared<MOCK_CMD>();    
    
    pQueue->Push( pcmd );
    pQueue->Push( pcmd );
    pQueue->Push( make_shared<_HardStopCmd>() );
    pQueue->Push( pcmd );  

    IStatePtr startState = make_shared<OrdinaryState>(pQueue);
    StartCmd cmd(startState);
  
    // проверяем, что после команды  _HardStopCmd команды не работают
    EXPECT_CALL(*pcmd, Execute()).Times(2);
    EXPECT_NO_THROW(cmd.Execute());
}

string state_getType(IStatePtr c)
{
    int status;  
   
    const type_info& typeInfo = typeid(*c);
    char* demangled = abi::__cxa_demangle(typeInfo.name(), nullptr, nullptr, &status);
    return (status == 0) ? demangled : typeInfo.name();
}

/// @brief проверить, что после команды move to, устанавливается состояние мувинг ту
/// проверка, что после запуска команды, команды переписываются в другую очередь 
/// (количество команд во второй очереди становится на одну меньше, чем было в первой до выполнения)
TEST(StateTest, move_to_cmd_work )
{
    CmdQueuePtr pQueue = make_shared<CmdQueue>();
    IoC::Resolve<  ICommandPtr, string, IResolverContainerPtr >("IoC.Register", "State", 
        make_container (
        function<IStatePtr()>([&](){
           return make_shared<OrdinaryState>(pQueue);
        })
    ))->Execute();
    
    CmdQueuePtr pOtherQueue = make_shared<CmdQueue>();    
    shared_ptr<MOCK_CMD> pcmd = make_shared<MOCK_CMD>();

    pQueue->Push( make_shared<MoveToCmd>(pQueue, pOtherQueue) );
    pQueue->Push( pcmd );
    pQueue->Push( pcmd );
    pQueue->Push( make_shared<_HardStopCmd>() );

    IStatePtr startState = make_shared<OrdinaryState>(pQueue);
    StartCmd cmd(startState);
  
   
    int qsize1 = pQueue->GetSize();
    
    EXPECT_NO_THROW(cmd.Execute());

    int qsize2 = pOtherQueue->GetSize();

    EXPECT_EQ( qsize2, qsize1 - 1 );

    IStatePtr ptr = IoC::Resolve<IStatePtr>("State");
    EXPECT_EQ(state_getType(ptr), "MovingToState");
}

/// @brief проверка команды run command
TEST(StateTest, run_cmd_work )
{ 
    CmdQueuePtr pQueue = make_shared<CmdQueue>();  
    ICommandPtr runCmd = make_shared<RunCmd>(pQueue);

    shared_ptr<MOCK_CMD> pcmd = make_shared<MOCK_CMD>();    
    pQueue->Push( pcmd );
    pQueue->Push( pcmd );
    pQueue->Push( make_shared<_HardStopCmd>() );
    
    runCmd->Execute();

    IStatePtr startState = IoC::Resolve<IStatePtr>("State");
    
    EXPECT_EQ(state_getType(startState), "OrdinaryState");
    StartCmd cmd(startState);
   
    EXPECT_CALL(*pcmd, Execute()).Times(2);
    EXPECT_NO_THROW(cmd.Execute());

   
}


#endif