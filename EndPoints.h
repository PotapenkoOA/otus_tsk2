#ifndef __ENDPOINT_H__
#define __ENDPOINT_H__

#include <boost/json.hpp>
#include <string>
#include <map>

using namespace std;
#include "game.h"

#include "EPsrv/endpoint.h"
#include "EPsrv/jwt_library.h"

/// маршрутитзация и распаковка
class Endpoint
{
    ep_server srv;
    map<string, IGamePtr> m_mapGames;
    //mapGames["123"] = pgame;
   
    public:
    Endpoint(  )
    {
       // m_pRouter = pRouter;
       if( !srv.connected( 34567 ) )
            return;
    }

    string ReceiveMessage()
    {
        string client_message = "";
        srv.listen(client_message);
        return client_message;
    }

    bool MakeCommand( string strMessage )
    {
       
        /// распаковка строки в структуру
        boost::json::value jmsg = boost::json::parse(strMessage);
        string jwt = jmsg.at("jwt").as_string().c_str();
        
        try{
            verify_jwt( jwt );
        }catch(exception& e)
        {
            cout<<"Exception!"<<endl;
            return false;
        }
        boost::json::object base_value;
        decode_jwt(jwt, base_value );
        string gameId =  base_value["game_id"].as_string().c_str();
        
        if( !m_mapGames.count(gameId) )
        {
            IGamePtr pgame = make_shared<AnyGame>();        
            m_mapGames[gameId] = pgame;
        }       
         
        return m_mapGames[gameId]->AddCommand( base_value["iss"].as_string().c_str(), jmsg );
    }
};

#endif