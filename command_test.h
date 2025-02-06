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
    ICommand *command = new GetExceptionCommand();

    EXPECT_ANY_THROW(command->Execute());
}

TEST(CommandTest, test1)
{
    // Реализовать Команду, которая записывает информацию о выброшенном исключении в лог.
    ICommand *command = new WriteToLogCommand(new GetExceptionCommand, new OrdinaryException(), "test play");

    EXPECT_NO_THROW(command->Execute());
}

TEST(CommandTest, test2)
{
   //Реализовать Команду, которая повторяет Команду, выбросившую исключение.
    ICommand *command = new DoublerCommand(new GetExceptionCommand());
   
    EXPECT_ANY_THROW(command->Execute());

    command = new DoublerCommand(new WriteToLogCommand(new GetExceptionCommand, new OrdinaryException(), "test play"));

    EXPECT_NO_THROW(command->Execute());
}

TEST(CommandTest, test3)
{
    //создать новую команду, точно такую же как в пункте 6. Тип этой команды будет показывать, что Команду не удалось выполнить два раза.    
   ICommand *command = new TriplerCommand(new GetExceptionCommand(), new OrdinaryException() );

   EXPECT_ANY_THROW(command->Execute());

   delete command;

   command = new TriplerCommand(new WriteToLogCommand(new GetExceptionCommand, new OrdinaryException(), "test play"), new OrdinaryException());

   EXPECT_NO_THROW(command->Execute());

   // command->Execute();
}


#endif