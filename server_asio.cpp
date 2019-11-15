#include <iostream>

#include "server/tcp_connection.hpp"
#include "server/matchmaking_server.hpp"
#include <boost/asio.hpp>

int main()
{
  try
  {
    boost::asio::io_context io_context;
    Matchmaking::MatchmakingServer server(io_context);
    io_context.run();
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
