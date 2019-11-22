#include "tcp_connection.hpp"

namespace Matchmaking {

TCPConnection::TCPConnection(boost::asio::io_context& io_context, GameQueueManager& game_queue_manager)
  : socket_(io_context)
  , game_queue_manager_(game_queue_manager)
{
}

TCPConnection::~TCPConnection()
{
  // Remove this user from the queue

  if (game_queue_ != NULL)
  {
    game_queue_->erase(*user_);
  }
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
  do_read_find_game_header();	
}

void TCPConnection::do_read_find_game_header()
{
  try
  {
    auto self(shared_from_this());
    boost::asio::async_read(socket_,
        boost::asio::buffer(find_game_packet_.data(), FindGamePacket::header_length),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (!ec && find_game_packet_.decode_header())
          {
            do_read_find_game_body();
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

void TCPConnection::do_read_find_game_body()
{
  try
  {
    auto self(shared_from_this());
    boost::asio::async_read(socket_,
        boost::asio::buffer(find_game_packet_.body(), find_game_packet_.body_length()),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
	  try
	  {
            if (!ec)
            {
  	      if (find_game_packet_.decode_body())
  	      {
  	        std::cout << "USER ID: " << find_game_packet_.get_user_id() << std::endl;
  	        std::cout << "Game Type: " << find_game_packet_.get_game_type() << std::endl;
  	        if (game_queue_manager_.is_valid_game_type(find_game_packet_.get_game_type()))
	        {
	          // Get game queue and insert user into queue
  	          game_queue_ = &(game_queue_manager_.get_game_queue(find_game_packet_.get_game_type()));
		  User temp_user(find_game_packet_.get_user_id(),
				 socket_.remote_endpoint().address().to_string(),
				 boost::bind(&Matchmaking::TCPConnection::host_game, this, _1, _2),
		                 boost::bind(&Matchmaking::TCPConnection::join_game, this, _1));
		  user_ = &temp_user;
  	          game_queue_->push(temp_user);
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

void TCPConnection::host_game(StartGameCallback start_game_callback, GameType host_game_type)
{

  HostPacket host_packet(host_game_type);
  // TODO: See if both of these encode statements can be replaced with a single encode method in Packet class
  host_packet.encode_body();
  host_packet.encode_header();
  boost::asio::async_write(socket_,
      boost::asio::buffer(host_packet.data(), host_packet.body_length()),
      [this](boost::system::error_code ec, std::size_t /*length*/)
      {
        if (!ec)
	{
	  // Call a read to read the process ID back from the user
	}
      });

  // FOr now use fake
  std::cout << "HOST USER ID: " << user_->get_user_id() << std::endl;
  JoinPacket join_packet("localhost", "12345");
  start_game_callback(join_packet);
}

void TCPConnection::do_read_join_header()
{
//  boost::asio::async_read(socket_,
//      boost::asio::buffer(
}

void TCPConnection::do_read_join_body()
{


}

void TCPConnection::join_game(JoinPacket join_packet)
{
  std::cout << "Finding game with " << join_packet.get_ip_address() << ":"<< join_packet.get_pid() << std::endl;
}
}
