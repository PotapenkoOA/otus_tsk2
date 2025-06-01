#ifndef __THREADCMD_TEST__
#define __THREADCMD_TEST__

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../IoCcontainer.h"
#include "../command.h"
#include "../CommandQueue.h"
#include "../ThreadCmd.h"

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


/// @brief проверка команды старт
TEST(ThreadCmdTest, start_cmd )
{
    CmdQueue queue;
        /// проверять моками вызов функции с параметрами
    MOCK_CMD mcmd;
    queue.Push(&mcmd);

    CmdQueue *pQueue = &queue;
    StartCmd cmd(&queue);
  
    EXPECT_CALL(mcmd, Execute()).WillOnce(Return());
    EXPECT_NO_THROW(cmd.Execute());
}

/// @brief проверка команды хард стоп
TEST(ThreadCmdTest, hard_stop_cmd )
{
    CmdQueue queue;
    /// проверять моками вызов функции с параметрами
    MOCK_CMD mcmd;
    HardStopCmd stop_cmd;
    queue.Push(&mcmd);
    queue.Push(&mcmd);
    queue.Push(&mcmd);
    queue.Push(&stop_cmd);
    queue.Push(&mcmd);

    CmdQueue *pQueue = &queue;
    StartCmd cmd(&queue);
   
    EXPECT_CALL(mcmd, Execute()).Times(3);   
    EXPECT_NO_THROW(cmd.Execute());
}

/// @brief проверка команды софт стоп
TEST(ThreadCmdTest, soft_stop_cmd )
{
    CmdQueue queue;
    /// проверять моками вызов функции с параметрами
    MOCK_CMD mcmd;
    SoftStopCmd stop_cmd;
    queue.Push(&mcmd);
    queue.Push(&mcmd);
    queue.Push(&mcmd);
    queue.Push(&stop_cmd);
    queue.Push(&mcmd);

    CmdQueue *pQueue = &queue;
    StartCmd cmd(&queue);
   
    EXPECT_CALL(mcmd, Execute()).Times(4);   
    EXPECT_NO_THROW(cmd.Execute());

    // больше не вызовется
    queue.Push(&mcmd);      
    EXPECT_CALL(mcmd, Execute()).Times(0);   
    EXPECT_NO_THROW(cmd.Execute());
}


#endif