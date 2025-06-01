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

ICommand* NewAttempt(ICommand* c, IException* e)
{
  return new DoublerCommand(c, e);
}

ICommand* OtherNewAttempt(ICommand* c, IException* e)
{
  return new TriplerCommand(c, e);
}
  
TEST(ExpectationLibraryTest, test1)
{
    // Реализовать обработчик исключения, который ставит Команду, пишущую в лог в очередь Команд.
    // проверить очередь команд до и после
    GetExceptionCommand cmd;
    OrdinaryException exc;
    WriteToLogCommand w_cmd;

    CommandQueue co;
    co.AddRuls( &cmd, &exc, &func );
    
    // проверить очередь исключений
    ASSERT_STRNE(co.GetLastCmdType().c_str(), getType(&w_cmd).c_str());

    // установить вызов исключения при вызове команды
    co.FirstCommand(&cmd);
    // вызвать обработчик тика
    co.Tick();

    // проверить очередь исключений
    ASSERT_STREQ(co.GetLastCmdType().c_str(), getType(&w_cmd).c_str());
   
}


TEST(ExpectationLibraryTest, test2)
{
    //Реализовать обработчик исключения, который ставит в очередь Команду - повторитель команды, выбросившей исключение.
    // проверить очередь команд до и после
    GetExceptionCommand cmd;
    OrdinaryException exc;
    DoublerCommand dbl_cmd;
    CommandQueue co;
    co.AddRuls(&cmd, &exc, &NewAttempt );
    
    // проверить очередь исключений
    ASSERT_STRNE(co.GetLastCmdType().c_str(), getType(&dbl_cmd).c_str());

    // установить вызов исключения при вызове команды
    co.FirstCommand(&cmd);
    // вызвать обработчик тика
    co.Tick();

    // проверить очередь исключений
    ASSERT_STREQ(co.GetLastCmdType().c_str(), getType(&dbl_cmd).c_str());
    
}

TEST(ExpectationLibraryTest, test3)
{
    // С помощью Команд из пункта 4 и пункта 6 реализовать следующую обработку исключений:
    // при первом выбросе исключения повторить команду, при повторном выбросе исключения записать информацию в лог.
    // проверить очередь команд до и после
    GetExceptionCommand cmd;
    DoublerCommand dbl_cmd;
    OrdinaryException exc;
    WriteToLogCommand w_cmd;

    CommandQueue co;
    co.AddRuls( &cmd,     &exc, &NewAttempt );
    co.AddRuls( &dbl_cmd, &exc, &func );
    
    // проверить очередь исключений
    ASSERT_STRNE(co.GetLastCmdType().c_str(), getType(&dbl_cmd).c_str());

    // установить вызов исключения при вызове команды
    co.FirstCommand(&cmd);
    // вызвать обработчик тика
    co.Tick();

    // проверить очередь исключений
    ASSERT_STREQ(co.GetLastCmdType().c_str(), getType(&dbl_cmd).c_str());

    // вызвать обработчик тика
    co.Tick();

    // проверить очередь исключений
    ASSERT_STREQ(co.GetLastCmdType().c_str(), getType(&w_cmd).c_str());
    
}

TEST(ExpectationLibraryTest, test4)
{
    //Реализовать стратегию обработки исключения - повторить два раза, потом записать в лог. 
    // Указание: создать новую команду, точно такую же как в пункте 6. 
    // Тип этой команды будет показывать, что Команду не удалось выполнить два раза.
    // проверить очередь команд до и после
    GetExceptionCommand cmd;
    DoublerCommand dbl_cmd;
    TriplerCommand trp_cmd;
    WriteToLogCommand w_cmd;
    OrdinaryException exc;

    CommandQueue co;
    co.AddRuls( &cmd,       &exc, &NewAttempt );
    co.AddRuls( &dbl_cmd,   &exc, &OtherNewAttempt );
    co.AddRuls( &trp_cmd,   &exc, &func );
    
    // проверить очередь исключений
    ASSERT_STRNE(co.GetLastCmdType().c_str(), getType(&dbl_cmd).c_str());

    // установить вызов исключения при вызове команды
    co.FirstCommand(&cmd);
    // вызвать обработчик тика
    co.Tick();
    // проверить очередь исключений
    ASSERT_STREQ(co.GetLastCmdType().c_str(), getType(&dbl_cmd).c_str());
    // вызвать обработчик тика
    co.Tick();
    // проверить очередь исключений
    ASSERT_STREQ(co.GetLastCmdType().c_str(), getType(&trp_cmd).c_str());
    // вызвать обработчик тика
    co.Tick();
    // проверить очередь исключений
    ASSERT_STREQ(co.GetLastCmdType().c_str(), getType(&w_cmd).c_str());
    
}

#endif