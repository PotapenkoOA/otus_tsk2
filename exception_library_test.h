#ifndef __EL_TESTS
#define __EL_TESTS

#include <gtest/gtest.h>
#include <gmock/gmock.h>


#include "command_queue.h"

using ::testing::Return;
using ::testing::Throw;
using ::testing::InSequence;

ICommand* func(ICommand* c, IException* e)
{
  return new WriteToLogCommand(c, e);
}

ICommand* func2(ICommand* c, IException* e)
{
  return new DoublerCommand(c);
}

ICommand* func3(ICommand* c, IException* e)
{
  return new TriplerCommand(c, e);
}



TEST(ExpectationLibraryTest, test1)
{
    // Реализовать обработчик исключения, который ставит Команду, пишущую в лог в очередь Команд.
    // проверить очередь команд до и после
    //ExceptionHandler::Register(getType(new GetExceptionCommand()), getType(new OrdinaryException()), &func2);

    CommandQueue co;
    co.AddRuls( new GetExceptionCommand(), new OrdinaryException(), &func );
    
    // проверить очередь исключений
    ASSERT_STRNE(co.GetLastCmdType().c_str(), "WriteToLogCommand");

    // установить вызов исключения при вызове команды
    co.FirstCommand(new GetExceptionCommand());
    // вызвать обработчик тика
    co.Tick();

    // проверить очередь исключений
    ASSERT_STREQ(co.GetLastCmdType().c_str(), "WriteToLogCommand");

    
}


TEST(ExpectationLibraryTest, test2)
{
    //Реализовать обработчик исключения, который ставит в очередь Команду - повторитель команды, выбросившей исключение.
    // проверить очередь команд до и после
    
    CommandQueue co;
    co.AddRuls( new GetExceptionCommand(), new OrdinaryException(), &func2 );
   // co.AddRuls( new DoublerCommand()), new OrdinaryException(), &func2 );
    
    // проверить очередь исключений
    ASSERT_STRNE(co.GetLastCmdType().c_str(), "DoublerCommand");

    // установить вызов исключения при вызове команды
    co.FirstCommand(new GetExceptionCommand());
    // вызвать обработчик тика
    co.Tick();

    // проверить очередь исключений
    ASSERT_STREQ(co.GetLastCmdType().c_str(), "DoublerCommand");
    
}

TEST(ExpectationLibraryTest, test3)
{
    // С помощью Команд из пункта 4 и пункта 6 реализовать следующую обработку исключений:
    // при первом выбросе исключения повторить команду, при повторном выбросе исключения записать информацию в лог.
    // проверить очередь команд до и после
    
    CommandQueue co;
    co.AddRuls( new GetExceptionCommand(), new OrdinaryException(), &func2 );
    co.AddRuls( new DoublerCommand(),      new OrdinaryException(), &func );
    
    // проверить очередь исключений
    ASSERT_STRNE(co.GetLastCmdType().c_str(), "DoublerCommand");

    // установить вызов исключения при вызове команды
    co.FirstCommand(new GetExceptionCommand());
    // вызвать обработчик тика
    co.Tick();

    // проверить очередь исключений
    ASSERT_STREQ(co.GetLastCmdType().c_str(), "DoublerCommand");

    // вызвать обработчик тика
    co.Tick();

    // проверить очередь исключений
    ASSERT_STREQ(co.GetLastCmdType().c_str(), "WriteToLogCommand");
    
}

TEST(ExpectationLibraryTest, test4)
{
    //Реализовать стратегию обработки исключения - повторить два раза, потом записать в лог. 
    // Указание: создать новую команду, точно такую же как в пункте 6. 
    // Тип этой команды будет показывать, что Команду не удалось выполнить два раза.
    // проверить очередь команд до и после
    
    CommandQueue co;
    co.AddRuls( new GetExceptionCommand(), new OrdinaryException(), &func2 );
    co.AddRuls( new DoublerCommand(),      new OrdinaryException(), &func3 );
    co.AddRuls( new TriplerCommand(),      new OrdinaryException(), &func );
    
    // проверить очередь исключений
    ASSERT_STRNE(co.GetLastCmdType().c_str(), "DoublerCommand");

    // установить вызов исключения при вызове команды
    co.FirstCommand(new GetExceptionCommand());
    // вызвать обработчик тика
    co.Tick();
    // проверить очередь исключений
    ASSERT_STREQ(co.GetLastCmdType().c_str(), "DoublerCommand");
    // вызвать обработчик тика
    co.Tick();
    // проверить очередь исключений
    ASSERT_STREQ(co.GetLastCmdType().c_str(), "TriplerCommand");
    // вызвать обработчик тика
    co.Tick();
    // проверить очередь исключений
    ASSERT_STREQ(co.GetLastCmdType().c_str(), "WriteToLogCommand");
    
}

#endif