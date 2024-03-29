#ifndef MATCHMAKING_GAME_QUEUE_HPP
#define MATCHMAKING_GAME_QUEUE_HPP

#include <boost/bind.hpp>
#include <string>
#include <queue>
#include <unordered_map>

#include "game_type.hpp"
#include "user.hpp"
#include "join_packet.hpp"

namespace Matchmaking
{

class GameQueue
{
public:
  GameQueue(int min_game_size, int max_game_size, GameType game_type) 
  : min_game_size_(min_game_size)
  , max_game_size_(max_game_size)
  , cur_queue_size_(0)
  , game_type_(game_type)
  {
  }

  size_t size()
  {
    return cur_queue_size_;
  }

  virtual void push(std::shared_ptr<Matchmaking::User>& user) = 0;

  // Return the user_id of the item that was popped
  virtual std::weak_ptr<User> pop() = 0;

  // Erase user from queue. Returns true if user was found and erased.
  virtual bool erase(std::shared_ptr<User>& user_to_erase) = 0;

  virtual void prepare_game() = 0;
  
  virtual void start_game(JoinPacket join_packet) = 0;

protected:
  // Users in queue
  // Using weak_ptr because connection may get dropped while User in queue
  std::queue<std::weak_ptr<User>> game_queue_;
  // Keep track of current users in queue and amount of times as user has been added to the queue
  std::unordered_map<std::string, int> user_map_;
  // The game type this queue represents
  GameType game_type_;
  const int min_game_size_;
  const int max_game_size_;
  size_t cur_queue_size_;
  bool is_preparing_game_;

};

}

#endif // MATCHMAKING_GAME_QUEUE_HPP

