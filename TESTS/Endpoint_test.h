#ifndef __THREADCMD_TEST__
#define __THREADCMD_TEST__

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../IoCcontainer.h"
#include "../CommandInterpreter.h"

using ::testing::Return;
using ::testing::Throw;
using ::testing::InSequence;

#include <iostream>
#include <string>
#include <thread>
#include <map>

using namespace std;

#include "../json-develop/single_include/nlohmann/json.hpp"

/// @brief проверка разбора сообщения
TEST(InterpreterCmdTest, parse_msg )
{
    IGame *pgame = new AnyGame();
    map<string, IGame*> mapGames;
    mapGames["123"] = pgame;

    string Message = R"({"gameId":"123","objectId":"cowboy_bibop","cmdId":"move", "args":[2,3,1]})";

    Endpoint ep(&mapGames, Message);
    ep.MakeCommand();

    delete pgame;
    SUCCEED();
}

/// @brief проверка постановки команды, заданной текстом в очередь игры
TEST(InterpreterCmdTest, add_interpreter_cmd )
{
    IGame *pgame = new AnyGame();
    map<string, IGame*> mapGames;
    mapGames["123"] = pgame;

    string Message = R"({"gameId":"123","objectId":"cowboy_bibop","cmdId":"move", "args":[2,3,1]})";

    Endpoint ep(&mapGames, Message);
    ep.MakeCommand();

    delete pgame;
    SUCCEED();
}



#endif