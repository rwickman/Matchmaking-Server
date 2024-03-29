#ifndef MATCHMAKING_FIND_GAME_PACKET_HPP
#define MATCHMAKING_FIND_GAME_PACKET_HPP


#include <string>
#include <nlohmann/json.hpp>

#include "packet.hpp"
#include "game_type.hpp"
#include "packet_type.hpp"

namespace Matchmaking
{

class FindGamePacket : public Packet
{
public:
  enum { header_length = 8 };
  enum { max_body_length = 512 };

  FindGamePacket();

  std::string get_user_id();

  GameType get_game_type();

  bool encode();

  bool decode_body();

protected:
  // In the future user identification may need its own class
  std::string user_id_;
  GameType game_type_;

};

}

#endif // MATCHMAKING_FIND_GAME_PACKET_HPP
