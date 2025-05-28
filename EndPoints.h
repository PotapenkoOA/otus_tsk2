#ifndef __ENDPOINT_H__
#define __ENDPOINT_H__

#include <string>
#include <iostream>
#include <map>

using namespace std;

#include "IResolverContainer.h"
#include "json-develop/single_include/nlohmann/json.hpp"
#include "command.h"
#include "IoCcontainer.h"
#include "CommandQueue.h"
#include "game.h"

/// маршрутитзация и распаковка
class Endpoint
{
    map<string, IGamePtr> *m_pRouter; 
   
    public:
    Endpoint( map<string, IGamePtr> *pRouter )
    {
        m_pRouter = pRouter;
    }

    bool MakeCommand( string strMessage )
    {
        /// распаковка строки в структуру
        nlohmann::json jmsg = nlohmann::json::parse(strMessage);
        
        IGamePtr pgame = (*m_pRouter)[jmsg["gameId"]];
        if( pgame == nullptr )
        {            
            throw bad_cast();
        }

        return pgame->AddCommand( jmsg );
    }
};

#endif