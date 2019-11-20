#include <iostream>
#include "deathmatch_game_queue.hpp"

namespace Matchmaking
{
  
  DeathmatchGameQueue::DeathmatchGameQueue() : GameQueue(2)
  {
  }

  void DeathmatchGameQueue::push(std::string user_id)
  {
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
    
    game_queue_.push(user_id);
    
    if (cur_queue_size_ >= min_game_size_)
    {
      std::cout << "READY TO START GAME" << std::endl;
    }
  }

  std::string DeathmatchGameQueue::pop()
  {
    std::string next_user_id = game_queue_.front();
    game_queue_.pop();

    // While the user is duplicated in the queue
    std::unordered_map<std::string,int>::iterator user_it = user_map_.find(next_user_id);
    while (user_it->second >= 2)
    {
      user_it->second -= 1;
      
      next_user_id = game_queue_.front();
      game_queue_.pop();

      user_it = user_map_.find(next_user_id);
    }

    // Remove popped user from map 
    user_map_.erase(user_it);
    cur_queue_size_ -= 1;
    return next_user_id;
  }

  void DeathmatchGameQueue::start_game()
  {
    
  }
}
