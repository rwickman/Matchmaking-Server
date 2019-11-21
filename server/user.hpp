#ifndef MATCHMAKING_USER_HPP
#define MATCHMAKING_USER_HPP

#include <string>
#include <functional>

#include "join_packet.hpp"

namespace Matchmaking
{

// Used by game queue to send servers join packet to all users
using StartGameCallback = std::function<void(JoinPacket)>;

class User
{
public:

  User(std::string user_id,
       std::string ip_address,
       std::function<void(StartGameCallback)> host_callback,
       std::function<void(JoinPacket)> join_callback);

  std::string get_user_id();

  std::string get_ip_address();

  std::function<void(StartGameCallback)> host_callback_;
  
  std::function<void(JoinPacket)> join_callback_;

private:
  std::string user_id_;
  std::string ip_address_; 
};

}



#endif // MATCHMAKING_USER_HPP
