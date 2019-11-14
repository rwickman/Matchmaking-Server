#include "matchmaking_server.hpp"

namespace Matchmaking {

MatchmakingServer::MatchmakingServer(boost::asio::io_context& io_context)
    : io_context_(io_context),
      acceptor_(io_context, tcp::endpoint(tcp::v4(), 13))
  {
    start_accept();
  }

void MatchmakingServer::start_accept()
{
    tcp_connection::pointer new_connection =
      tcp_connection::create(io_context_);

    acceptor_.async_accept(new_connection->socket(),
        boost::bind(&tcp_server::handle_accept, this, new_connection,
          boost::asio::placeholders::error));
}

void MatchmakingServer::handle_accept(TCPConnection::pointer new_connection,
		const boost::system::error_code& error)
{
  if (!error)
  {
    new_connection->start();
  }

  start_accept();
}

}
