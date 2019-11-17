#ifndef MATCHMAKING_JOIN_PACKET_HPP
#define MATCHMAKING_JOIN_PACKET_HPP


#include <string>

#include "packet.hpp"
#include <nlohmann/json.hpp>

namespace Matchmaking
{

class JoinPacket : public Packet
{
public:
  enum { header_length = 8 };
  enum { max_body_length = 512 };
  enum GameType {
    ELIMINATION = 0,
  };

  JoinPacket();

  std::string get_user_id();

  int get_game_type();

  bool decode_join();

protected:
  // In the future user identification may need its own class
  std::string user_id;
  GameType game_type;

};

}

#endif // MATCHMAKING_JOIN_PACKET_HPP
