#include <boost/json.hpp>
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>

#include "endpoint.h"

namespace json = boost::json;

std::string game_id;
std::string my_jwt;

class agent{
    ep_client client;
    
    public:

    
    void autontification(  std::string srv_ip, unsigned int port )
    { 
        std::cout << "Auth Server IP: "<<srv_ip<<std::endl;
        client.connect( srv_ip, port );
    }

    void gameserver(  std::string srv_ip, unsigned int port )
    {
        std::cout << "Game Server IP: "<<srv_ip<<std::endl;
        client.connect( srv_ip, port );
    }

    void send_new_game_msg(  )
    {
        std::string result = "";

        json::object message1;
        message1["cmd"] = "new_game"; 
        message1["gamer"] = {"han_solo", "malcolm_reynolds", "spike_spiegel"};    
        client.chat( json::serialize(message1) , result);

        json::value jv;
        try
        {
            boost::system::error_code ec;
            jv = json::parse( result, ec );
            if( ec )
                std::cout << "Parsing failed: " << ec.message() << "\n";
        }
        catch( std::bad_alloc const& e)
        {
            std::cout << "Parsing failed: " << e.what() << "\n";
        }  
        
        game_id = json::value_to<std::string>(jv.at("game_id"));
    }

    void send_ask_jwt_msg(  )
    {
        std::string result = "";

        json::object message;
        message["cmd"] = "get_jwt"; 
        message["game_id"] = game_id;
        message["user_id"] = "han_solo";
        std::cout << "json:" << json::serialize(message) <<std::endl ;
        client.chat( json::serialize(message) , result);

        json::value jv;
        try 
        {
            boost::system::error_code ec;
            jv = json::parse( result, ec );
            if( ec )
                std::cout << "Parsing failed: " << ec.message() << "\n";
        }
        catch( std::bad_alloc const& e)
        {
            std::cout << "Parsing failed: " << e.what() << "\n";
        }   
        my_jwt = jv.at("jwt").as_string().c_str();
        //std::cout << <<std::endl;
    }

    void send_jwt_msg(  )
    {
        std::string result = "";
        json::object message;
        message["cmd"] = "log"; 
        message["jwt"] = my_jwt;
        message["msg"] = "Hello,world!";
        std::cout << "json:" << json::serialize(message) <<std::endl ;
        client.chat( json::serialize(message) , result);
    }

};

int main() {
    std::string auth_ip  = "127.0.0.1";
    unsigned int auth_port = 12345;

    std::string game_ip  = "127.0.0.1";
    unsigned int game_port = 34567;
    
    agent gamer;

    gamer.autontification( "127.0.0.1", 12345);
    
    gamer.send_new_game_msg();
 
    gamer.send_ask_jwt_msg();  

    gamer.gameserver( "127.0.0.1", 34567);

    gamer.send_jwt_msg( );

    std::cout<<"happy end\n";

    return 0;
}