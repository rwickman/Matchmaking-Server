#ifndef MATCHMAKING_GAME_QUEUE_MANAGER_HPP
#define MATCHMAKING_GAME_QUEUE_MANAGER_HPP

#include "game_type.hpp"
#include "deathmatch_game_queue.hpp"

namespace Matchmaking
{

class GameQueueManager
{
public:
  GameQueueManager();

  bool is_valid_game_type(GameType game_type);
 
  std::shared_ptr<GameQueue> get_game_queue(GameType game_type);

private:
  std::shared_ptr<DeathmatchGameQueue> deathmatch_game_queue_;

};	

}

#endif // MATCHMAKING_GAME_QUEUE_MANAGER_HPP  
