#include "game_queue_manager.hpp"

namespace Matchmaking
{

GameQueueManager::GameQueueManager()
{
}

bool GameQueueManager::is_valid_game_type(GameType game_type)
{
  if (game_type == GameType::Deathmatch)
  {
    return true;
  }
  return false;
}

GameQueue& GameQueueManager::get_game_queue(GameType game_type)
{
  if (game_type == GameType::Deathmatch)
  {
    return deathmatch_game_queue_;
  }
}

}
