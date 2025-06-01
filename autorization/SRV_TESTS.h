#ifndef __SRV_TEST__
#define __SRV_TEST__

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <iostream>
#include <string>
#include <thread>
#include <map>

using namespace std;

#include <boost/json.hpp>
#include "IoCcontainer.h"

using ::testing::Return;
using ::testing::Throw;
using ::testing::InSequence;

#include "endpoint.h"
#include "AutorizationCommand.h"
#include "CommandQueue.h"
#include "ThreadCmd.h"

using namespace std;

/// @brief успешная проверка 
TEST(AUTO_SRVR, good_jwt_msg )
{
    string client_message;
    string reply_message;

    IoC::Resolve<ICommandPtr, string, IResolverContainer*>("IoC.Register", "Cmd.new_game", 
            new ResolverContainer< function<ICommandPtr(boost::json::value)>> (
            function([](boost::json::value data){ cout<<"current game\n"; return make_shared<ParceGamerListCmd>(data);})
            ))->Execute();

    IoC::Resolve<ICommandPtr, string, IResolverContainer*>("IoC.Register", "Cmd.get_jwt", 
            new ResolverContainer< function<ICommandPtr(boost::json::value)>> (
            function([](boost::json::value data){ cout<<"new jwt\n"; return make_shared<CalculateJWTCmd>(data);})
            ))->Execute();

    ep_server srv(80008) ;
    
    try{
        
        CmdQueuePtr pq = make_shared<CmdQueue>();
        pq->Push( make_shared<ListenCmd>(&srv) );
        pq->Push( make_shared<HandleMsgCmd>() );
        pq->Push( make_shared<ReplyCmd>(&srv) );

        pq->Push( make_shared<ListenCmd>(&srv) );
        pq->Push( make_shared<HandleMsgCmd>() );
        pq->Push( make_shared<ReplyCmd>(&srv) );

        StartCmd cmd( pq );
        cmd.Execute();
    }
    catch(exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }

    SUCCEED();
}

#endif