#ifndef MATCHMAKING_GAME_QUEUE_HPP
#define MATCHMAKING_GAME_QUEUE_HPP

#include <string>
#include <queue>
#include <unordered_map>

#include "game_type.hpp"

namespace Matchmaking
{

class GameQueue
{
public:
  GameQueue(int min_game_size) 
  :  min_game_size_(min_game_size)
  ,  cur_queue_size_(0)
  {
  }

  size_t size()
  {
    return cur_queue_size_;
  }

  virtual void push(std::string user_id) = 0;

  // Return the user_id of the item that was popped
  virtual std::string pop() = 0;

protected:
  std::queue<std::string> game_queue_;
  // Keep track of current users in queue and amount of times as user has been added to the queue
  std::unordered_map<std::string, int> user_map_;

  const int min_game_size_;
  size_t cur_queue_size_;

};

}

#endif // MATCHMAKING_GAME_QUEUE_HPP

