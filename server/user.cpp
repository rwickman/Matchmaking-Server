#include "user.hpp"

namespace Matchmaking
{

User::User(std::string user_id,
	   std::string ip_address,
	   std::function<void(StartGameCallback)> host_callback,
	   std::function<void(std::string, std::string)> find_game_callback)
  : user_id_(user_id)
  , ip_address_(ip_address)
  , host_callback_(host_callback)
  , find_game_callback_(find_game_callback)
{
}

std::string User::get_user_id()
{
  return user_id_;
}

std::string User::get_ip_address()
{
  return ip_address_;
}

}
