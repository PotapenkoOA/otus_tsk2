#include <string>
#include <iostream>
#include <map>

using namespace std;

#include "IResolverContainer.h"
#include "json-develop/single_include/nlohmann/json.hpp"
#include "command.h"
#include "IoCcontainer.h"
#include "CommandQueue.h"
#include "InterpretCommand.h"

class IObject
{
    public:
    virtual void set( string name, IResolverContainer* property ) = 0;
    virtual IResolverContainer *get( string name ) = 0;
};

struct Message
{
    string gameId;
    string objId;
    string cmdId;
    IResolverContainer* args;
};

class IGame
{
    public:
    virtual bool AddCommand(nlohmann::json jmsg) = 0;
    virtual string GetState() = 0;
    virtual void Play() = 0;
};

class AnyGame : public IGame
{
    CmdQueue *pCmdQueue;
    public:
    AnyGame()
    {
        pCmdQueue = new CmdQueue();
    }
    ~AnyGame()
    {
        delete pCmdQueue;
    }

    bool AddCommand(nlohmann::json jmsg) 
    {
       
        string objName = jmsg["objectId"];
        string cmdName = jmsg["cmdId"];
        
        cout<<"objName: "<<objName<<", cmdName: "<<cmdName<<", args: "<<jmsg["args"]<<endl;
        InterpretCommand cmd(jmsg);

        //pCmdQueue->Push();

        return true;
    }
    string GetState()
    {
        return "";
    }
    
    void Play()
    {

    }
};

/// маршрутитзация и распаковка
class Endpoint
{
    map<string, IGame*> *m_pRouters; 
    string m_strMessage;
   
    public:
    Endpoint( map<string, IGame*> *pRouters, string strMessage )
    {
        m_pRouters = pRouters;
        m_strMessage = strMessage;
    }

    bool MakeCommand( )
    {
        /// распаковка строки в структуру
        nlohmann::json jmsg = nlohmann::json::parse(m_strMessage);

        Message msg;
        IGame* pgame = (*m_pRouters)[jmsg["gameId"]];
        if( pgame == nullptr )
            throw bad_cast();
        
        pgame->AddCommand( jmsg );

        return true;
    }
};

