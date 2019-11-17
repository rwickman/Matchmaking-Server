#ifndef MATCHMAKING_GAME_QUEUE_HPP
#define MATCHMAKING_GAME_QUEUE_HPP

#include <string>
#include <queue>
#include <unordered_map>

#include "gametype.hpp"

namespace Matchmaking
{

class GameQueue
{
public:
  GameQueue(int min_game_size);

  size_t size()
  {
    return game_queue.size();
  }

  virtual void push(std::string user_id) = 0;

  // Return the user_id of the item that was popped
  virtual std::string pop() = 0;

protected:
  std::queue<std::string> game_queue;
  // Keep track of current users in queue and amount of times as user has been added to the queue
  std::unordered_map<std::string, int> user_map;

  const int min_game_size;
  int cur_queue_size;

};

}

#endif // MATCHMAKING_GAME_QUEUE_HPP

