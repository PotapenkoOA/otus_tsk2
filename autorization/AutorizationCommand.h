#ifndef __COMMANDS__
#define __COMMANDS__

#include <boost/json.hpp>
#include <string>
#include <list>
#include <map>

using namespace std;

#include "command.h"
#include "jwt_library.h"
#include "IoCcontainer.h"

using SharedListPtr = shared_ptr<list<string>>;
std::map<string, SharedListPtr> gameMap;

class ParceGamerListCmd: public ICommand
{
    boost::json::value m_data;

    public:
    ParceGamerListCmd(boost::json::value data)
    {
        m_data = data;
    }

    void Execute()
    {
        //cout<<"ParceGamerListCmd\n";
        SharedListPtr gamerList = make_shared<list<string>>();
        json::object message;
        try
        {
            json::array arr = m_data.at("gamer").get_array();        
            for(auto gamer : arr)
            {     
            gamerList->push_back(json::value_to<std::string>( gamer ));
            }
            
            unsigned long _gameId = (unsigned long)gamerList.get();  
            string gameId = to_string( _gameId );         
            message["game_id"] = gameId;
            gameMap[gameId] = gamerList;
            string result = json::serialize(message);

            //std::cout << "json:" << result <<" ptr:"<< gameId <<std::endl ;           

            IoC::Resolve<ICommandPtr, string, IResolverContainer*>("IoC.Register", "MessageToClient", 
            new ResolverContainer< function<string()>> (
            function([result](){ /*cout<<"client message:"<<result<<"\n"; */ return result;})
            ))->Execute();
        }
        catch(std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
    }
};

class CalculateJWTCmd: public ICommand
{
    boost::json::value m_data;

    public:
    CalculateJWTCmd(boost::json::value data)
    {
        m_data = data;
    }

    void Execute()
    {
        string user_id = json::value_to<std::string>(m_data.at("user_id"));
        string game_id = json::value_to<std::string>(m_data.at("game_id"));
        
        json::object message;
        if( gameMap.count(game_id) == 0 )
        {    
            cout<<"error: game is not starting\n";
            return ;
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
            return ;
        }

        message["jwt"] = create_jwt( user_id, game_id);    

        string result = json::serialize(message);
        //std::cout << "json:" << result <<std::endl ; 
        
        IoC::Resolve<ICommandPtr, string, IResolverContainer*>("IoC.Register", "MessageToClient", 
            new ResolverContainer< function<string()>> (
            function([result](){ /*cout<<"client message:"<<result<<"\n";*/ return result;})
            ))->Execute();
    
        //return result;
    }
};

class HandleMsgCmd:public ICommand
{
    public:
    HandleMsgCmd()
    {}

    void Execute()
    {
        string current_msg = IoC::Resolve<string>( "MessageFromClient");
        boost::json::value j = boost::json::parse(current_msg);
        string value = j.at("cmd").as_string().c_str();


        ICommandPtr cmd = IoC::Resolve<ICommandPtr >("Cmd."+value, j );
        cmd->Execute();        
    }
};



class ListenCmd:public ICommand
{
    ep_server *m_srv;
    public:
    ListenCmd( ep_server *psrv )
    {
        m_srv = psrv;
    }
    void Execute()
    {
        string current_msg;
        m_srv->listen(current_msg);

        cout<< current_msg <<endl;

        IoC::Resolve<ICommandPtr, string, IResolverContainer*>("IoC.Register", "MessageFromClient", 
            new ResolverContainer< function<string()>> (
            function([current_msg](){ /*cout<<"client message:"<<current_msg<<"\n";*/ return current_msg;})
            ))->Execute();
    }
};

class ReplyCmd:public ICommand
{
    ep_server *m_srv;
    public:
    ReplyCmd( ep_server *psrv )
    {
        m_srv = psrv;
    }
    void Execute()
    {
        string current_msg = IoC::Resolve<string>( "MessageToClient");
        
        m_srv->reply(current_msg);
    }
};


#endif