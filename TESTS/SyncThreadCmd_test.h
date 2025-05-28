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

    mutex m;
    condition_variable cvar;
    bool conditional = false;
  
    EXPECT_CALL(mcmd, Execute()).WillOnce([&cvar, &conditional](){  conditional = true; cvar.notify_one();});

    EXPECT_NO_THROW(cmd.Execute());

    /// проверка запуска потока с использованием условной переменной
    unique_lock<mutex> lock(m);
    cvar.wait(lock, [&conditional]{return conditional;});
    SUCCEED();
}

/// @brief проверка команды хард стоп
TEST(ThreadCmdTest, hard_stop_cmd )
{
    CmdQueue queue;
    /// проверять моками вызов функции с параметрами
    MOCK_CMD mcmd;
    MOCK_CMD thread_notify_cmd;
    HardStopCmd stop_cmd;

    
    queue.Push(&mcmd);
    queue.Push(&mcmd);
    queue.Push(&thread_notify_cmd);
    queue.Push(&stop_cmd);
    queue.Push(&mcmd);

    CmdQueue *pQueue = &queue;
    StartCmd cmd(&queue);

    mutex m;
    condition_variable cvar;
    bool conditional = false;
    
    EXPECT_CALL(mcmd, Execute()).Times(2);
    EXPECT_CALL(thread_notify_cmd, Execute()).WillOnce([&cvar, &conditional](){  conditional = true; cvar.notify_one();});
           
    EXPECT_NO_THROW(cmd.Execute());

    /// проверка запуска потока обработки команд с использованием условной переменной
    unique_lock<mutex> lock(m);
    cvar.wait(lock, [&conditional]{return conditional;});
    SUCCEED();
}

/// @brief проверка команды софт стоп
TEST(ThreadCmdTest, soft_stop_cmd )
{
    CmdQueue queue;
    /// проверять моками вызов функции с параметрами
    MOCK_CMD mcmd;
    MOCK_CMD thread_notify_cmd;
    SoftStopCmd stop_cmd;
    queue.Push(&thread_notify_cmd);
    queue.Push(&mcmd);
    queue.Push(&mcmd);
    queue.Push(&stop_cmd);
    queue.Push(&mcmd);

    CmdQueue *pQueue = &queue;
    StartCmd cmd(&queue);

    mutex m;
    condition_variable cvar;
    bool conditional = false;
   
    EXPECT_CALL(thread_notify_cmd, Execute()).WillOnce([&cvar, &conditional](){  conditional = true; cvar.notify_one();});
    EXPECT_CALL(mcmd, Execute()).Times(3);   
    EXPECT_NO_THROW(cmd.Execute());

    /// проверка запуска потока обработки команд с использованием условной переменной
    unique_lock<mutex> lock(m);
    cvar.wait(lock, [&conditional]{return conditional;});
    SUCCEED();
}

#endif