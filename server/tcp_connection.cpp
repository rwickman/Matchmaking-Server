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
  do_read_join_header();	
}

void TCPConnection::do_read_join_header()
{
  auto self(shared_from_this());
  boost::asio::async_read(socket_,
      boost::asio::buffer(join_packet_.data(), JoinPacket::header_length),
      [this, self](boost::system::error_code ec, std::size_t /*length*/)
      {
        if (!ec && join_packet_.decode_header())
        {
          do_read_join_body();
        }
        else
        {
	  std::cerr << "ERROR GETTING HEADER FOR JOIN" << std::endl;
        }
      });
/*  std::cout << "HANDLED READ" << std::endl;
  try
  {
    if (!error && bytes_transferred > 0)
    {
      std::string join_str(recv_buf_.data());
      std::cout << "ABOUT TO PARSE: " << join_str << std::endl;
      nlohmann::json join_json = nlohmann::json::parse(join_str);
      // Consider making this a class later on
      std::string user_id = join_json["User ID"].get<std::string>();
      int req_game_type = join_json["Game Type"].get<int>();
      std::cout << "USER ID: " << user_id << std::endl;
      std::cout << "GAME TYPE: " << req_game_type << std::endl;
    }
  }
  catch(std::exception& e)
  {
    // TODO: Log this message to a file
    std::cerr << e.what() << std::endl;
  }*/
}

void TCPConnection::do_read_join_body()
{
  auto self(shared_from_this());
  boost::asio::async_read(socket_,
      boost::asio::buffer(join_packet_.body(), join_packet_.body_length()),
      [this, self](boost::system::error_code ec, std::size_t /*bytes transferred*/)
      {
        if (!ec)
	{
	  if (join_packet_.decode_join())
	  {
	    std::cout << "USER ID: " << join_packet_.get_user_id() << std::endl;
	    std::cout << "Game Type: " << join_packet_.get_game_type() << std::endl;
	    // Perform other callback here
	  }
	}
      });
}

void TCPConnection::handle_write(const boost::system::error_code& /*error*/, 
		size_t /*bytes_transferred*/)
{
}

}
