#ifndef __ENDPOINT__
#define __ENDPOINT__

#include <boost/asio.hpp>
#include <iostream>
#include <thread>

using boost::asio::ip::tcp;

class ep_server
{
    
    tcp::socket *psocket;

    public:
    ep_server(unsigned int port)
    {
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), port));

        std::cout << "Server started. Waiting for client..." << std::endl;

        psocket = new tcp::socket(io_context);
        acceptor.accept(*psocket);
    }

    ~ep_server()
    {

        delete psocket;
    }
    

    bool listen(std::string &message)
    {
        char data[1024];
        
        std::memset(data, 0, 1024);
        boost::system::error_code error;

        try{
        // Read message from clients
        size_t length = psocket->read_some(boost::asio::buffer(data), error);
        
        if (error == boost::asio::error::eof) return false; // Connection closed
        else if (error) throw boost::system::system_error(error);

        }catch(std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
            message = "";
            return false;
        }

        message = data;
        //std::cout << "Client: " << message << std::endl;
        
        return true;
    }

    bool reply(std::string response)
    {
        boost::system::error_code error;
        
        boost::asio::write(*psocket, boost::asio::buffer(response), error);

        //std::cout << "Auth: "<<response<<std::endl;

        return true;
    }
};

#endif