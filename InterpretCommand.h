#ifndef _INTERPRET_COMMAND_
#define _INTERPRET_COMMAND_

#include <string>
#include <map>
#include <list>
#include <iostream>

using namespace std;

#include "IResolverContainer.h"

#include "command.h"
#include "IoCcontainer.h"
#include "older_task/vector2.h"

#include "json-develop/single_include/nlohmann/json.hpp"

/// парсинг команды по имени из json
class InterpretCommand: public ICommand
{
    list<ICommandPtr> m_cmds;
    public:
    InterpretCommand( nlohmann::json jmsg , IObjectPtr object)
    {
        string cmdId = jmsg["cmdId"];
        nlohmann::json arr = jmsg["args"];

        if( object == nullptr )
            throw bad_cast();
        
       if( arr.size() == 2 )
       {
            cout << " a: "<< arr[0]<<","<< arr[1]<<" Object."+cmdId<<endl;   
            Vector2 v( arr[0], arr[1] );
            
            ICommandPtr cmd = IoC::Resolve<ICommandPtr, IObjectPtr, Vector2 >("Object."+cmdId, object, v );
            m_cmds.push_back(cmd);
        }
        else
        {
            ICommandPtr cmd = IoC::Resolve<ICommandPtr, IObjectPtr >("Object."+cmdId, object );
            m_cmds.push_back(cmd);
        }
    }

    void Execute()
    {
        for(auto it : m_cmds )
        {
            it->Execute();
        }
    }
};

#endif