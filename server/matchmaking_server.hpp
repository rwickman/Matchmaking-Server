#ifndef MATCHMAKING_MATCHMAKING_SERVER_HPP
#define MATCHMAKING_MATCHMAKING_SERVER_HPP

#include "tcp_connection.hpp"
#include <boost/asio.hpp>

namespace Matchmaking {

using boost::asio::ip::tcp;

class MatchmakingServer
{
  public:
    MatchmakingServer(boost::asio::io_context& io_context);
  
  private:
    void start_accept();

    void handle_accept(boost::shared_ptr<TCPConnection> new_connnection,
		    const boost::system::error_code& error);

    boost::asio::io_context& io_context_;
    tcp::acceptor acceptor_;
};

}

#endif // MATCHMAKING_MATCHMAKING_SERVER_HPP
