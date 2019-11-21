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
  // Only add user_id to queue if not already found or if erased previously
  if (user_it == user_map_.end())
  {
    user_map_.insert(std::pair<std::string, int>(user_id, 1));
    cur_queue_size_ += 1;
  }
  else if (user_it->second <= 0)
  {
    user_it->second = 1;
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
    // TODO: Check if game is already is session and is joinable
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

bool DeathmatchGameQueue::erase(User& user_to_erase)
{
  std::unordered_map<std::string,int>::iterator user_it = user_map_.find(user_to_erase.get_user_id());
  if (user_it != user_map_.end())
  {
    // This will make it so when it pops off the queue it will not be added
    user_it->second = 0;
    cur_queue_size_ -= 1;
    std::cout << "ERASED USER " << user_it->first << std::endl;
    return true;
  }
  else
  {
    return false;
  }
}


void DeathmatchGameQueue::prepare_game()
{
  // Pick the user that will act as the server
  User user_host = pop();
  user_host.host_callback_(boost::bind(&Matchmaking::DeathmatchGameQueue::start_game, this, _1)); 
}

void DeathmatchGameQueue::start_game(JoinPacket& join_packet)
{
  // Initialize to 1 to account for the server
  int cur_game_size = 1; 
  while(cur_queue_size_ > 0 && cur_game_size < max_game_size_)
  {
    User cur_user = pop();
    std::cout << "ADDING USER: " << cur_user.get_user_id() << std::endl;
    cur_game_size += 1;
    cur_user.join_callback_(join_packet);
  }
}

}
