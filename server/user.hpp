#ifndef MATCHMAKING_USER_HPP
#define MATCHMAKING_USER_HPP

#include <string>
#include <functional>

namespace Matchmaking
{

class User
{
public:
  User(std::string user_id, std::string ip_address, std::function<void(std::string)> start_callback);

  std::string get_user_id();

  std::string get_ip_address();

  std::function<void(std::string)> start_callback_;

private:
  std::string user_id_;
  std::string ip_address_; 
};

}



#endif // MATCHMAKING_USER_HPP
