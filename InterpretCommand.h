#include <string>
#include <map>
#include <list>
#include <vector>

using namespace std;

#include "IResolverContainer.h"

#include "command.h"
#include "IoCcontainer.h"

#include "json-develop/single_include/nlohmann/json.hpp"

/// парсинг команды по имени из json
class InterpretCommand: public ICommand
{
    list<ICommand*> m_cmds;
    public:
    InterpretCommand( nlohmann::json jmsg )
    {
        string objectId = jmsg["objectId"];
        ///map<string, IResolverContainer*> *object= IoC::Resolve<map<string, IResolverContainer*>*>( "Game.Objects", objectId );

        string cmdId = jmsg["cmdId"];
        nlohmann::json arr = jmsg["args"];
        
        vector<int> *pv = new vector<int>();
        for( auto a :arr  )
        {
            cout << " a: " <<a<<endl;
            
            pv->push_back(a);
        }
        ///ICommand* cmd = IoC::Resolve<ICommand*, map<string, IResolverContainer*>*, vector<int>*>( cmdId, object, pv );
        ///m_cmds.push_back(cmd);
    }

    void Execute()
    {
        for(auto it : m_cmds )
        {
            it->Execute();
        }
    }
};