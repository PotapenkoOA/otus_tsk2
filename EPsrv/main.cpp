#include <boost/json.hpp>
#include <iostream>
#include <string>

#include "endpoint.h"

#include "commands.h"

using namespace std;

bool HandleMessage(string json_str, string &reply_str)
{
    boost::json::value j = boost::json::parse(json_str);
    string value = j.at("cmd").as_string().c_str();
   
    if (value == "log")
    {
        reply_str = VerifyCmd(j);
    }
    else reply_str = "";

    return true;
}

int main() {
    while(1)
    {
        ep_server srv;
        if( !srv.connected( 34567 ) )
            return 0;
        
        try{
            string client_message;
            string reply_message;
            while( srv.listen( client_message ) )
            {
                HandleMessage( client_message, reply_message );
                srv.reply( reply_message );

                client_message = "";
            }
        }
        catch(exception& e) {
            cerr << "Exception: " << e.what() << endl;
        }
    }
    return 1;
}