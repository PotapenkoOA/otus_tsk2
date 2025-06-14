#ifndef __GAME_H__
#define __GAME_H__

#include <boost/json.hpp>

#include "older_task/vector2.h"
#include "InterpretCommand.h"
#include "ThreadCmd.h"

#include <string>
#include <iostream>
#include <map>

using namespace std;

class IGame
{
    public:
    virtual bool AddCommand( string objName, boost::json::value jmsg) = 0;
    virtual string GetState() = 0;
    virtual void Start() = 0;
    virtual void Stop() = 0;
};

using IGamePtr = std::shared_ptr<IGame>;


class AnyGame : public IGame
{
    CmdQueuePtr pCmdQueue;
    map<string, IObjectPtr> m_mapObjects;
    IObjectPtr m_mRules;

    public:
    AnyGame()
    {       
        pCmdQueue = make_shared<CmdQueue>();
        
        IoC::Resolve<ICommandPtr, string, IResolverContainerPtr>("IoC.Register", "Game.Objects", 
            make_container (
            function<IObjectPtr(string)>([&](string objectId){
                return m_mapObjects[objectId];
            })
        ))->Execute();
        
    }
    
    bool AddCommand(string objName, boost::json::value jmsg) 
    {
        //string objectId = jmsg.at("objectId").as_string().c_str();
        if( m_mapObjects.count(objName) )
            m_mapObjects[objName] = IoC::Resolve<IObjectPtr, IObjectPtr> ("IoC.Scope.New", nullptr );
        
        auto pcmd = make_shared<InterpretCommand>(jmsg, m_mapObjects[objName]);

        pCmdQueue->Push(pcmd);

        return true;
    }

    string GetState()
    {
        return "";
    }
    
    bool AddRuls( IObjectPtr newRules )
    {
        m_mRules = newRules;       

        return true;
    }

    void Start()
    {
        
        StartCmd cmd(pCmdQueue);
        cmd.Execute();
    }

    void Stop()
    {
        
        pCmdQueue->Push(make_shared<HardStopCmd>());
        
    }
};

#endif