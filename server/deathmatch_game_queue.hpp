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

  void push(User user);

  User pop();
  
  void prepare_game();

  void start_game();
};

}

#endif // MATCHMAKING_DEATHMATCH_GAME_QUEUE_HPP
