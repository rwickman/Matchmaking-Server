#include "tcp_connection.hpp"
#include <ctime>

namespace Matchmaking {

std::string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}

TCPConnection::TCPConnection(boost::asio::io_context& io_context) : socket_(io_context)
{
}

boost::shared_ptr<TCPConnection> 
TCPConnection::create(boost::asio::io_context& io_context)
{
  return boost::shared_ptr<TCPConnection>(new TCPConnection(io_context));
}

tcp::socket& TCPConnection::socket()
{
  return socket_;
}

void TCPConnection::start()
{
    nlohmann::json msg_json;
    msg_json["IP"] = "localhost";
    msg_json["Other"] = "What is up dog?";
    std::string msg = msg_json.dump(); 
    boost::asio::async_write(socket_, boost::asio::buffer(msg),
        boost::bind(&TCPConnection::handle_write, shared_from_this(),
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
}

void TCPConnection::handle_write(const boost::system::error_code& /*error*/, 
		size_t /*bytes_transferred*/)
{
}

}
