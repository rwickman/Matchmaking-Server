#ifndef MATCHMAKING_TCP_CONNECTION_HPP
#define MATCHMAKING_TCP_CONNECTION_HPP

#include <string>
#include <array>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <nlohmann/json.hpp>

#include "find_game_packet.hpp"
#include "join_packet.hpp"
#include "host_packet.hpp"
#include "ack_packet.hpp"
#include "game_queue.hpp"
#include "game_queue_manager.hpp"
#include "game_type.hpp"
#include "ack_type.hpp"
#include "user.hpp"


namespace Matchmaking
{
class ConnectionLock;

using boost::asio::ip::tcp;

class TCPConnection
  : public boost::enable_shared_from_this<TCPConnection>
{
public:
  static boost::shared_ptr<TCPConnection> create(boost::asio::io_context& io_context, GameQueueManager& game_queue_manager);

  tcp::socket& socket();

  void start();

  ~TCPConnection();

private:
  TCPConnection(boost::asio::io_context& io_context, GameQueueManager& game_queue_manager); 


  void do_read_find_game_header();
  
  void do_read_find_game_body();

  void host_game(StartGameCallback start_game_callback, GameType& host_game_type);
 
  void do_read_join_header();

  void do_read_join_body();

  void do_read_ack_header();
  
  void do_read_ack_body();

  void join_game(JoinPacket join_packet);

  tcp::socket socket_;
  FindGamePacket find_game_packet_;
  JoinPacket join_packet_;
  AckPacket ack_packet_;
  std::shared_ptr<StartGameCallback> start_game_callback_;
  GameQueueManager& game_queue_manager_;
  std::shared_ptr<GameQueue> game_queue_;
  std::shared_ptr<User> user_;
  bool is_hosting_;
  // As long as something as access to shared pointer this connection will alive
  // In the futrue this may need to be fixed
};

}
#endif // MATCHMAKING_TCP_CONNECTION_HPP
