#include <iostream>
#include "deathmatch_game_queue.hpp"

namespace Matchmaking
{
  
DeathmatchGameQueue::DeathmatchGameQueue() : GameQueue(2, 4)
{
}

void DeathmatchGameQueue::push(User user)
{
  std::string user_id = user.get_user_id();
  std::unordered_map<std::string,int>::iterator user_it = user_map_.find(user_id);
  // Only add user_id to queue if not already found
  if (user_it == user_map_.end())
  {
    user_map_.insert(std::pair<std::string, int>(user_id, 1));
    cur_queue_size_ += 1;
  }
  else
  {
    user_it->second += 1;
    std::cout << "AMOUNT OF TIMES ADDED " << user_id << ": " <<  user_it->second << std::endl;  
  }
  
  game_queue_.push(user);
  
  if (cur_queue_size_ >= min_game_size_)
  {
    // TODO: Check if game is already is session and is find_gameable
    std::cout << "READY TO START GAME" << std::endl;
    prepare_game();
  }

}

User DeathmatchGameQueue::pop()
{
  User next_user = game_queue_.front();
  game_queue_.pop();

  // While the user is duplicated in the queue
  std::unordered_map<std::string,int>::iterator user_it = user_map_.find(next_user.get_user_id());
  while (user_it->second >= 2)
  {
    user_it->second -= 1;
    
    next_user = game_queue_.front();
    game_queue_.pop();

    user_it = user_map_.find(next_user.get_user_id());
  }

  // Remove popped user from map 
  user_map_.erase(user_it);
  cur_queue_size_ -= 1;
  return next_user;
}


void DeathmatchGameQueue::prepare_game()
{
  User user_host = pop();
  user_host.host_callback();  
}

void DeathmatchGameQueue::start_game()
{
/*
  std::string cur_game_ip;
  int cur_game_size = 0;
  while(cur_queue_size_ > 0 && cur_game_size < max_game_size_)
  {
    User cur_user = pop();
    std::cout << "ADDING USER: " << cur_user.get_user_id() << std::endl;
    cur_game_size += 1;
    if (cur_game_size == 1)
    {
      cur_game_ip = cur_user.get_ip_address();
    }
    // This could return a response regarding if it still available or it has created the game
    cur_user.start_callback_(cur_game_ip);
  }
*/
}

}
