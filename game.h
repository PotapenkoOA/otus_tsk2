#ifndef __GAME_H__
#define __GAME_H__

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
    virtual bool AddCommand(nlohmann::json jmsg) = 0;
    virtual string GetState() = 0;
    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual bool AddShip( string name, IObjectPtr newObject ) = 0;
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
        
        IoC::Resolve<ICommandPtr, string, IResolverContainer*>("IoC.Register", "Game.Objects", 
            new ResolverContainer< function<IObjectPtr(string)>> (
            function<IObjectPtr(string)>([&](string objectId){
                return m_mapObjects[objectId];
            })
        ))->Execute();
        
    }
    
    bool AddCommand(nlohmann::json jmsg) 
    {
        string objectId = jmsg["objectId"];
        auto pcmd = make_shared<InterpretCommand>(jmsg, m_mapObjects[objectId]);

        pCmdQueue->Push(pcmd);

        return true;
    }

    string GetState()
    {
        return "";
    }
    
    bool AddShip( string name, IObjectPtr newObject )
    {
        if(m_mapObjects.count(name) > 0)
            return false;

        m_mapObjects[name] = newObject;
        
        return true;
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