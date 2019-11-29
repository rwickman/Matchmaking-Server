#include "tcp_connection.hpp"

namespace Matchmaking {

TCPConnection::TCPConnection(boost::asio::io_context& io_context, GameQueueManager& game_queue_manager)
  : socket_(io_context)
  , game_queue_manager_(game_queue_manager)
{
}

TCPConnection::~TCPConnection()
{
  std::cout << "DESTROYING TCPConnection" << std::endl;
  // Remove this user from the queue
  if (game_queue_ != NULL)
  {
    game_queue_->erase(user_);
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
        [this, self](boost::system::error_code ec, std::size_t length)
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
        [this, self](boost::system::error_code ec, std::size_t length)
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
  	          game_queue_ = std::move(game_queue_manager_.get_game_queue(find_game_packet_.get_game_type()));
		  user_ = std::make_shared<User>(find_game_packet_.get_user_id(),
				                 socket_.remote_endpoint().address().to_string(),
				                 boost::bind(&Matchmaking::TCPConnection::host_game, this, _1, _2),
		                                 boost::bind(&Matchmaking::TCPConnection::join_game, this, _1));
  	          game_queue_->push(user_);
		  do_read_ack_header();
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

void TCPConnection::host_game(StartGameCallback start_game_callback, GameType& host_game_type)
{
  start_game_callback_ = std::make_shared<StartGameCallback>(start_game_callback);
  HostPacket host_packet(host_game_type);
  host_packet.encode();
  auto self(shared_from_this());
  boost::asio::async_write(socket_,
      boost::asio::buffer(host_packet.data(), host_packet.length()),
      [this, self](boost::system::error_code ec, std::size_t /*length*/)
      {
        if (!ec)
	{
	  is_hosting_ = true;
	}
	else
	{
	}
      });
}

void TCPConnection::do_read_join_header()
{
  auto self(shared_from_this());
  boost::asio::async_read(socket_,
      boost::asio::buffer(join_packet_.data(), JoinPacket::header_length),
      [this, self](boost::system::error_code ec, std::size_t length)
      {
        if (!ec && join_packet_.decode_header())
	{
	  std::cout << "DECODED JOIN HEADER: " << join_packet_.body_length() << std::endl;
	  do_read_join_body();
	}
      });
}

void TCPConnection::do_read_join_body()
{
  auto self(shared_from_this());
  boost::asio::async_read(socket_,
      boost::asio::buffer(join_packet_.body(), join_packet_.body_length()),
      [this, self](boost::system::error_code ec, std::size_t /*length*/)
     {
       if (!ec)
       {
	 if (join_packet_.decode_body())
	 {
           (*start_game_callback_)(join_packet_);
           // release the lock
	 }
	 else
	 {
	 std::cerr << "COULD NOT DECODE JOIN PACKET FROM HOST!" << std::endl;
	 }
       }
     });
}

void TCPConnection::do_read_ack_header()
{
  auto self(shared_from_this());
  boost::asio::async_read(socket_,
      boost::asio::buffer(ack_packet_.data(), ack_packet_.header_length),
      [this, self](boost::system::error_code ec, std::size_t length)
     {
       std::cout << "LENGTH: " << length << std::endl;
       std::cout << ec << std::endl;
       if (!ec && ack_packet_.decode_header())
       {
	 do_read_ack_body();
       }
       else
       {
         //socket_.close();
       }
     });
}

void TCPConnection::do_read_ack_body()
{
  auto self(shared_from_this());
  std::cout << "BODY LEN: " << ack_packet_.body_length() << std::endl;
  boost::asio::async_read(socket_,
      boost::asio::buffer(ack_packet_.body(), ack_packet_.body_length()),
      [this, self](boost::system::error_code ec, std::size_t length)
     {
       std::cout << "LENGTH: " << length << std::endl;
       std::cout << ec << std::endl;
       if (!ec)
       {
         if (ack_packet_.decode_body())
         {
	   std::cout << "READ ACK" << std::endl;
	   if (ack_packet_.get_ack_type() == AckType::Error)
	   {
	     throw ack_error();
	   }
	   else if (is_hosting_)
	   {
             do_read_join_header();
	   }
         }
         else
         {
	   //socket_.close();
	     //throw ack_error();
         }
       }
       else
       {
         //socket_.close()
       }
     });
}

void TCPConnection::join_game(JoinPacket join_packet)
{
  auto self(shared_from_this());
  boost::asio::async_write(socket_,
      boost::asio::buffer(join_packet.data(), join_packet.length()),
      [this, self](boost::system::error_code ec, std::size_t length)
      {
        // release the lock
      });
}

}
