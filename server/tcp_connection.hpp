#ifndef MATCHMAKING_TCP_CONNECTION_HPP
#define MATCHMAKING_TCP_CONNECTION_HPP

#include <string>
#include <array>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <nlohmann/json.hpp>

#include "join_packet.hpp"
#include "game_queue.hpp"
#include "game_queue_manager.hpp"

namespace Matchmaking
{

using boost::asio::ip::tcp;

class TCPConnection
  : public boost::enable_shared_from_this<TCPConnection>
{
public:
  static boost::shared_ptr<TCPConnection> create(boost::asio::io_context& io_context, GameQueueManager& game_queue_manager);

  tcp::socket& socket();

  void start();

private:
  TCPConnection(boost::asio::io_context& io_context, GameQueueManager& game_queue_manager); 

  void do_read_join_header();
  
  void do_read_join_body();

  tcp::socket socket_;
  JoinPacket join_packet_;
  GameQueue* game_queue_;
  GameQueueManager& game_queue_manager_;
};

}
#endif // MATCHMAKING_TCP_CONNECTION_HPP
