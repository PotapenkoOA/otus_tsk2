#ifndef COMMAND_TESTS
#define COMMAND_TESTS

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "command.h"
#include "exception_library.h"

using ::testing::Return;
using ::testing::Throw;
using ::testing::InSequence;

TEST(CommandTest, test0)
{
    // проверить команду вызывающую исключение
    GetExceptionCommand command;

    EXPECT_ANY_THROW(command.Execute());
}

TEST(CommandTest, test1)
{
    // Реализовать Команду, которая записывает информацию о выброшенном исключении в лог.
    GetExceptionCommand cmd;
    OrdinaryException exc;

    WriteToLogCommand command(&cmd, &exc, "test play");

    EXPECT_NO_THROW(command.Execute());
}

TEST(CommandTest, test2)
{
   //Реализовать Команду, которая повторяет Команду, выбросившую исключение.
    GetExceptionCommand cmd;
    OrdinaryException exc;

    DoublerCommand command( &cmd, &exc );

    EXPECT_ANY_THROW(command.Execute());

    
    DoublerCommand command2(new WriteToLogCommand(&cmd, &exc, "test play"), &exc);
    EXPECT_NO_THROW(command2.Execute());
}

TEST(CommandTest, test3)
{
    //создать новую команду, точно такую же как в пункте 6. Тип этой команды будет показывать, что Команду не удалось выполнить два раза.   
    GetExceptionCommand cmd;
    OrdinaryException exc;

    TriplerCommand command( &cmd, &exc );

    EXPECT_ANY_THROW(command.Execute());
   
    TriplerCommand command2(new WriteToLogCommand(&cmd, &exc, "test play"), &exc);
    EXPECT_NO_THROW(command2.Execute());
}


TEST(CommandTest, getTypeFunctionTest)
{
    //проверить функции возврата типа значения по указателю на базовый тип   
    GetExceptionCommand cmd;
    OrdinaryException exc;
    DoublerCommand dcmd( &cmd, &exc );
    TriplerCommand tcmd( &cmd, &exc );
    WriteToLogCommand wcmd( &cmd, &exc );

    ICommand* pCmd = &cmd;
    ASSERT_STREQ(getType(pCmd).c_str(), "GetExceptionCommand");

    pCmd = &dcmd;
    ASSERT_STREQ(getType(pCmd).c_str(), "DoublerCommand");
    pCmd = &tcmd;
    ASSERT_STREQ(getType(pCmd).c_str(), "TriplerCommand");
    pCmd = &wcmd;
    ASSERT_STREQ(getType(pCmd).c_str(), "WriteToLogCommand");

    ASSERT_STREQ(getType(&exc).c_str(), "OrdinaryException");
}


#endif