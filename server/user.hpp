#ifndef MATCHMAKING_USER_HPP
#define MATCHMAKING_USER_HPP

#include <string>

#include "tcp_connection.hpp"

namespace Matchmaking
{

struct User
{
  std::string user_id;
  TCPConnection& connection;
};

}



#endif // MATCHMAKING_USER_HPP
