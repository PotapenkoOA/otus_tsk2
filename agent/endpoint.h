#include <boost/json.hpp>
#include <boost/asio.hpp>
#include <iostream>

namespace json = boost::json;

using boost::asio::ip::tcp;

class ep_client{
    tcp::socket *psocket;
    public:
    void connect(const std::string& server_ip, uint32_t port)
    {
        try {
            boost::asio::io_context io_context;
            psocket = new tcp::socket(io_context);
            psocket->connect(tcp::endpoint(boost::asio::ip::make_address(server_ip), port));

            std::cout << "Connected to server at " << server_ip << std::endl;
        } catch (std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
    }

    void query(std::string message, std::string &result) {
        try {
            boost::system::error_code error;
            boost::asio::write(*psocket, boost::asio::buffer(message), error);

            if (error) throw boost::system::system_error(error);

            char data[1024];
            std::memset(data, 0, sizeof(data));
            size_t length = psocket->read_some(boost::asio::buffer(data), error);
            if (error == boost::asio::error::eof) return;
            else if (error) throw boost::system::system_error(error);
            
            result = data;
            //std::cout << "Server: " << data << std::endl;

        } catch (std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
    }

    void diconnect()
    {
        psocket->close();
    }
};






