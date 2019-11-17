#ifndef MATCHMAKING_DEATHMATCH_GAME_QUEUE_HPP
#define MATCHMAKING_DEATHMATCH_GAME_QUEUE_HPP

#include <string>
#include <utility>

#include "game_queue.hpp"

namespace Matchmaking
{

class DeathmatchGameQueue : public GameQueue
{
public:
  DeathmatchGameQueue();

  void push(std::string user_id);

  std::string pop();
};

}

#endif // MATCHMAKING_DEATHMATCH_GAME_QUEUE_HPP
