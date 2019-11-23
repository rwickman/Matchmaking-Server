#include "game_queue_manager.hpp"

namespace Matchmaking
{

GameQueueManager::GameQueueManager()
  : deathmatch_game_queue_(std::make_shared<DeathmatchGameQueue>())
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

std::shared_ptr<GameQueue> GameQueueManager::get_game_queue(GameType game_type)
{
  if (game_type == GameType::Deathmatch)
  {
    return std::shared_ptr<DeathmatchGameQueue>(deathmatch_game_queue_);
  }
}

}
