#include "tcp_connection.hpp"

namespace Matchmaking {

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
  boost::asio::async_read(socket_,
	boost::asio::buffer(recv_buf_, 128),
	boost::bind(
	  &TCPConnection::handle_read_join, shared_from_this(),
	  boost::asio::placeholders::error,
	  boost::asio::placeholders::bytes_transferred));
  

    /*
    nlohmann::json msg_json;
    std::string msg = msg_json.dump(); 
    boost::asio::async_write(socket_, boost::asio::buffer(msg),
        boost::bind(&TCPConnection::handle_write, shared_from_this(),
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  */
}

void TCPConnection::handle_read_join(const boost::system::error_code& error, 
		size_t bytes_transferred)
{
  std::cout << "HANDLED READ" << std::endl;
  try
  {
    if (!error && bytes_transferred > 0)
    {
      std::string join_str = recv_buf_.data();
      nlohmann::json join_json = nlohmann::json::parse(join_str);
      // Consider making this a class later on
      std::string user_id = join_json["User ID"].get<std::string>();
      int req_game_type = join_json["Game Type"].get<int>();
      std::cout << user_id << std::endl;
      std::cout << req_game_type << std::endl;
    }
  }
  catch(std::exception& e)
  {
    // TODO: Log this message to a file
    std::cerr << e.what() << std::endl;
  }
}

void TCPConnection::handle_write(const boost::system::error_code& /*error*/, 
		size_t /*bytes_transferred*/)
{
}

}
