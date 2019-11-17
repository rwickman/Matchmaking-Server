#include "matchmaking_server.hpp"

namespace Matchmaking {

MatchmakingServer::MatchmakingServer(boost::asio::io_context& io_context)
    : io_context_(io_context),
      acceptor_(io_context, tcp::endpoint(tcp::v4(), 12001))
  {
    start_accept();
  }

void MatchmakingServer::start_accept()
{
    boost::shared_ptr<TCPConnection> new_connection =
      TCPConnection::create(io_context_, game_queue_manager_);

    acceptor_.async_accept(new_connection->socket(),
        boost::bind(&MatchmakingServer::handle_accept, this, new_connection,
          boost::asio::placeholders::error));
}

void MatchmakingServer::handle_accept(boost::shared_ptr<TCPConnection> new_connection,
		const boost::system::error_code& error)
{
  if (!error)
  {
    new_connection->start();
  }

  start_accept();
}

}
