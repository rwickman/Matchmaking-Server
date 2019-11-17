#include "tcp_connection.hpp"

namespace Matchmaking {

TCPConnection::TCPConnection(boost::asio::io_context& io_context, GameQueueManager& game_queue_manager)
  : socket_(io_context)
  , game_queue_manager_(game_queue_manager)
{
}

boost::shared_ptr<TCPConnection> 
TCPConnection::create(boost::asio::io_context& io_context, GameQueueManager& game_queue_manager)
{
  return boost::shared_ptr<TCPConnection>(new TCPConnection(io_context, game_queue_manager));
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
  try
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
  }
  catch(std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}

void TCPConnection::do_read_join_body()
{
  try
  {
    auto self(shared_from_this());
    boost::asio::async_read(socket_,
        boost::asio::buffer(join_packet_.body(), join_packet_.body_length()),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
	  try
	  {
            if (!ec)
            {
  	      if (join_packet_.decode_join())
  	      {
  	        std::cout << "USER ID: " << join_packet_.get_user_id() << std::endl;
  	        std::cout << "Game Type: " << join_packet_.get_game_type() << std::endl;
  	        if (game_queue_manager_.is_valid_game_type(join_packet_.get_game_type()))
	        {
	          // Get game queue and insert user into queue
  	          game_queue_ = &(game_queue_manager_.get_game_queue(join_packet_.get_game_type()));
  	          game_queue_->push(join_packet_.get_user_id());
	        }
	        else
	        {
	          throw std::invalid_argument( "Invalid Game Type!" );
	        }
	      }
  	    }
	  }
	  catch(std::invalid_argument& e)
	  {
	    std::cerr << e.what() << std::endl;
	  }
	  catch(std::exception& e)
	  {
	    std::cerr << e.what() << std::endl;
	  }
        });
  }
  catch(std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}

}
