#ifndef MATCHMAKING_USER_HPP
#define MATCHMAKING_USER_HPP

#include <string>
#include <functional>

namespace Matchmaking
{

using StartGameCallback = std::function<void(std::string)>;

class User
{
public:

  User(std::string user_id,
       std::string ip_address,
       std::function<void(StartGameCallback)> host_callback,
       std::function<void(std::string, std::string)> find_game_callback);

  std::string get_user_id();

  std::string get_ip_address();

  std::function<void(start_game_callback)> host_callback_;
  
  std::function<void(std::string, std::string)> find_game_callback_;

private:
  std::string user_id_;
  std::string ip_address_; 
};

}



#endif // MATCHMAKING_USER_HPP
