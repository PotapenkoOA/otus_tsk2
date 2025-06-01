#ifndef __COMMANDS__
#define __COMMANDS__

#include <boost/json.hpp>
#include <string>
#include <list>
#include <map>

using namespace std;

#include "jwt_library.h"

using SharedListPtr = shared_ptr<list<string>>;
std::map<string, SharedListPtr> gameMap;

string VerifyCmd( boost::json::value data )
{
    string jwt = json::value_to<std::string>(data.at("jwt"));
    json::object message;
    try{
        verify_jwt(jwt);
        message["result"] = "success"; //fail
    }
    catch(std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
         message["result"] = "fail"; //fail
    }
   
    return json::serialize(message);
}

std::string NewGameCmd( boost::json::value data )
{
    SharedListPtr gamerList = make_shared<list<string>>();
    json::object message;
    try
    {
        json::array arr = data.at("gamer").get_array();        
        for(auto gamer : arr)
        {     
           gamerList->push_back(json::value_to<std::string>( gamer ));
        }
        
        unsigned long _gameId = (unsigned long)gamerList.get();  
        string gameId = to_string( _gameId );         
        message["game_id"] = gameId;
        gameMap[gameId] = gamerList;

        //std::cout << "json:" << json::serialize(message1) <<" ptr:"<< gameId <<std::endl ;
    }
    catch(std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    
    return json::serialize(message);
}

std::string GetJWTCmd( boost::json::value data )
{    
    string user_id = json::value_to<std::string>(data.at("user_id"));
    string game_id = json::value_to<std::string>(data.at("game_id"));
    
    json::object message;
    if( gameMap.count(game_id) == 0 )
    {    
        cout<<"error: game is not starting\n";
        return "";
    }
    
    SharedListPtr lst = gameMap[game_id];
    bool find = false;
    for( auto member : *lst.get())
    {    
       if( member == user_id )
        find = true;
    }
    if( !find )
    {    
        cout<<"error: you are not a gamer\n";
        return "";
    }

    message["jwt"] = create_jwt( user_id, game_id);    

    string result = json::serialize(message);
    std::cout << "json:" << result <<std::endl ; 
    
    return result;
}

#endif