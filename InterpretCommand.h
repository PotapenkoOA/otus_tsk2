#ifndef _INTERPRET_COMMAND_
#define _INTERPRET_COMMAND_

#include <boost/json.hpp>
#include <list>
#include <string>
#include <iostream>

#include "IResolverContainer.h"

#include "command.h"
#include "IoCcontainer.h"
#include "older_task/vector2.h"

using namespace std;

/// парсинг команды по имени из json
class InterpretCommand: public ICommand
{
    list<ICommandPtr> m_cmds;

    public:
    InterpretCommand( boost::json::value  jmsg, IObjectPtr object)
    {

        //string objectId = jmsg.at("objectId").as_string().c_str();
        string cmdId = jmsg.at("cmd").as_string().c_str();
       

        //if( object == nullptr )
        //    throw bad_cast();
        
        try
        {
            boost::json::array arr = jmsg.at("args").get_array();
            if( arr.size() == 2 )
            {
                //cout << " a: "<< arr[0]<<","<< arr[1]<<" Object."+cmdId<<endl;  
                int x =  arr[0].as_int64();
                int y = arr[1].as_int64();
                
                Vector2 v( x, y );
                
                ICommandPtr cmd = IoC::Resolve<ICommandPtr, IObjectPtr, Vector2 >("Object."+cmdId, object, v );
                m_cmds.push_back(cmd);                
            }
        }
        catch(exception& e)
        {
            //cout<<cmdId<<endl;
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