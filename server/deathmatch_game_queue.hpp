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

  void push(std::shared_ptr<Matchmaking::User>& user);

  std::weak_ptr<User> pop();
  
  bool erase(std::shared_ptr<User>& user_to_erase);
  
  void prepare_game();

  void start_game(JoinPacket join_packet);
};

}

#endif // MATCHMAKING_DEATHMATCH_GAME_QUEUE_HPP
