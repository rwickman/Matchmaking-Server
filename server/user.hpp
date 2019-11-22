#ifndef MATCHMAKING_USER_HPP
#define MATCHMAKING_USER_HPP

#include <string>
#include <functional>

#include "join_packet.hpp"
#include "game_type.hpp"

namespace Matchmaking
{

// Used by game queue to send servers join packet to all users
using StartGameCallback = std::function<void(JoinPacket&)>;
using HostCallback = std::function<void(StartGameCallback, GameType&)>;
using JoinCallback = std::function<void(JoinPacket&)>;

class User
{
public:

  User(std::string user_id,
       std::string ip_address,
       HostCallback host_callback,
       JoinCallback join_callback);

  std::string get_user_id();

  std::string get_ip_address();

  HostCallback host_callback_;
  
  JoinCallback join_callback_;

private:
  std::string user_id_;
  std::string ip_address_; 
};

}



#endif // MATCHMAKING_USER_HPP
